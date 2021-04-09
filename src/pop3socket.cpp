/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: pop3socket.cpp
 * Date: 28-02-2021
 */

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <map>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <gnutls/gnutls.h>
#include "pystring.h"
#include <mailutils/mime.h>

#include "globals.h"

#include "pop3socket.h"

using namespace std;

Pop3socket::Pop3socket() {}

Pop3socket::Pop3socket(std::string hostname, uint16_t port, bool is_encrypted) {
    _hostname = hostname;
    _port = port;
    _is_encrypted = is_encrypted;
}

void Pop3socket::fill_endpoint(string hostname, uint16_t port, bool is_encrypted) {
    _hostname = hostname;
    _port = port;
    _is_encrypted = is_encrypted;
}

int Pop3socket::_resolve_name() {
    hostent *resolved_host = gethostbyname(_hostname.c_str());
    if (resolved_host == nullptr){
        logger->error("Name resolution failed. Cannot resolve hostname: {}", _hostname);
        return RESOLV_ERR;
    }
    in_addr **ip_addr_ptr = (struct in_addr **) resolved_host->h_addr_list;
    _addr_family = resolved_host->h_addrtype;
    _ip_addr = inet_ntoa(*ip_addr_ptr[0]);
    logger->debug("Resolved name {} to IP address: {}", _hostname, (string) _ip_addr);
    return SUCCESS;
}

int Pop3socket::_create_bsd_socket() {
    _socket_descriptor = socket(_addr_family, SOCK_STREAM, 0);
    memset(&_socket_address, '\0', sizeof(_socket_address));
    _socket_address.sin_family = _addr_family;
    _socket_address.sin_port = htons(_port);

    inet_pton(_addr_family, _ip_addr.c_str(), &_socket_address.sin_addr);
    int err = ::connect(_socket_descriptor, (struct sockaddr *) &_socket_address, sizeof(_socket_address));

    if (err != SUCCESS) { 
        logger->error("Couldn't establish connection to server {}:{}", _hostname, _port);
        return err;
    }
    logger->debug("Successfully created socket connected with {}:{}", _hostname, _port);
    return SUCCESS;
}

int Pop3socket::_setup_gnutls() {
    gnutls_global_init();
    gnutls_certificate_allocate_credentials(&_xcred);
    gnutls_certificate_set_x509_system_trust(_xcred);

    gnutls_init(&_sess, GNUTLS_CLIENT);

    gnutls_server_name_set(_sess, GNUTLS_NAME_DNS, _hostname.c_str(),
                           strlen(_hostname.c_str()));
    gnutls_set_default_priority(_sess);
    gnutls_credentials_set(_sess, GNUTLS_CRD_CERTIFICATE, _xcred);
    gnutls_session_set_verify_cert(_sess, _hostname.c_str(), 0);

    gnutls_transport_set_int(_sess, _socket_descriptor);
    gnutls_handshake_set_timeout(_sess, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

    int err_handshake = gnutls_handshake(_sess);
    if (err_handshake != SUCCESS) {
        logger->error("Cannot establish TLS handshake with server {}:{}", _hostname, _port);
        return err_handshake;
    }
    logger->debug("Established GnuTLS handshake: {}", gnutls_session_get_desc(_sess));
    return SUCCESS;
}

int Pop3socket::connect() {
    int ret_resolv = _resolve_name();
    if (ret_resolv != 0) { return ret_resolv; }

    int ret_socket = _create_bsd_socket();
    if (ret_socket != 0) { return ret_socket; }

    if (_is_encrypted){
        int ret_gnutls = _setup_gnutls();
        if(ret_gnutls != 0){ return ret_gnutls; }
    }

    if(_recv().substr(0, 3) == "+OK"){
        _session_up = true;
        logger->debug("POP3 session established. Got +OK from server");
        return SUCCESS;
    } else {
        logger->error("Couldn't establish a POP3 session. Is the server speaking POP3?");
        return PROTOCOL_ERR;
    }
}

int Pop3socket::login(string username, string password) {
    if (!_session_up) { return NOT_CONNECTED_ERR; }
    if (_is_logged_in) { return ALREADY_LOGGED_IN_ERR; }
    _send("USER " + username);
    if (_recv().substr(0, 3) == "-ERR") {
        logger->error("Protocol error. Maybe the pipe is broken?"); 
        return PROTOCOL_ERR; 
    }

    _send("PASS " + password);
    string auth_response = _recv();
    if (auth_response.substr(0, 3) == "+OK") {
        _is_logged_in = true;
        logger->debug("Successfully authenticated user {} on server {}:{}", username, _hostname, _port);
        return SUCCESS;
    } else if (auth_response.substr(0, 11) == "-ERR [AUTH]"){
        logger->error("Login failed. Wrong credentials for user: {} provided", username);
        return WRONG_CREDENTIALS_ERR;
    } else {
        logger->error("Protocol error. Maybe the pipe is broken?");
        return PROTOCOL_ERR;
    }
}

bool Pop3socket::ping(){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("NOOP");
    string noop_response = _recv();
    if(noop_response.substr(0, 3) == "+OK"){
        logger->debug("Got ping back from {}:{}", _hostname, _port);
        return true;
    } else {
        logger->error("Background ping for {}:{} failed. Maybe the pipe is broken?", _hostname, _port);
        return false;
    }
}

int Pop3socket::get_mails(vector<mail_t> &mails){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("LIST");
    string list_response = _recv_to_end();
    if(list_response.substr(0, 3) != "+OK"){ return PROTOCOL_ERR; }
    vector<string> list_rows;
    vector<string> list_row_data;
    pystring::split(list_response, list_rows, "\n");
    list_rows.erase(list_rows.begin());
    for(string list_row : list_rows){
        list_row_data.clear();

        if (list_row.substr(0, 1) == ".") { break; }

        pystring::split(list_row, list_row_data, " ");

        mail_t new_mail(stoi(list_row_data.at(0)), stoi(list_row_data.at(1)));
        mails.push_back(new_mail);
    }

    return SUCCESS;
}

int Pop3socket::complete_mail(mail_t *mail){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    if (mail->uidl().length() != 0) { return SUCCESS; }
    mail->uidl(_get_uidl(mail->id()));
    mail->headers(_get_headers(mail->id()));
    return SUCCESS;
}

map<string, string> Pop3socket::_get_headers(uint16_t mailid){
    _send("TOP " + to_string(mailid) + " 0");
    string headers_response = _recv_to_end();
    map<string, string> headers;
    vector<string> headers_rows;
    vector<string> encoded_parts;
    pystring::split(headers_response, headers_rows, "\r\n");
    headers_rows.erase(headers_rows.begin());

    string key;
    string prev_key;
    string val;
    string decoded_val;
    for (string headers_row : headers_rows){
        if (headers_row.length() == 0) { break; }

        prev_key = key;
        key.clear();
        val.clear();
        decoded_val.clear();

        for(char c : headers_row){
            if(c == ':'){ break; }
            key += c;
        }

        try {
            val = headers_row.substr(key.length() + 2, string::npos);
        } catch (const std::out_of_range& oor_err){
            headers[prev_key] += headers_row;
            key = prev_key;
            continue;
        }

        if (key == "Subject"){
            char *decoded_part_val;
            mu_rfc2047_decode("UTF-8", val.c_str(), &decoded_part_val);
            val = (string) decoded_part_val;
        }

        headers[key] = val;
    }

    return headers;
}

string Pop3socket::_get_uidl(uint16_t mailid) {
    _send("UIDL " + to_string(mailid));
    string uidl_response = _recv();
    vector<string> uidl_data;
    pystring::split(uidl_response, uidl_data, " ");
    string return_uidl = uidl_data.at(2);
    return return_uidl.erase(return_uidl.length() - 2);
}

int Pop3socket::delete_mail(uint16_t mailid) {
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("DELE " + to_string(mailid));
    string dele_response = _recv();
    vector<string> dele_data;
    pystring::split(dele_response, dele_data, " ");
    if (dele_data.at(0) != "+OK") {
        return PROTOCOL_ERR;
    }
    return SUCCESS;
}

int Pop3socket::reset_mailbox() {
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("RSET");
    string rset_response = _recv();
    if (rset_response.substr(0, 3) != "+OK") {
        return PROTOCOL_ERR;
    }
    return SUCCESS;
}

int Pop3socket::download_mail(uint16_t mailid, string *mail_content) {
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("RETR " + to_string(mailid));
    *mail_content = _recv_to_end();
    if (mail_content->substr(0, 3) != "+OK") {
        return PROTOCOL_ERR;
    }
    mail_content->erase(0, mail_content->find("\n") + 1);
    mail_content->pop_back();
    return SUCCESS;
}

int Pop3socket::get_stats(stat_t *status){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("STAT");
    string stat_response = _recv();
    if(stat_response.substr(0, 3) != "+OK") { return PROTOCOL_ERR; }
    vector<string> stat_data;
    pystring::split(stat_response, stat_data, " ");
    status->mails = stoi(stat_data.at(1));
    status->bytes = stoi(stat_data.at(2));
    return SUCCESS;
}

inline bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

string Pop3socket::_recv_to_end(){
    char buf[512]{};

    string key = ".\r\n";
    string full_recv = "";
    string seg = "";

    while(!ends_with(seg, key)){
        if(_is_encrypted) {
            gnutls_record_recv(_sess, buf, sizeof(buf) - 1);
        } else {
            recv(_socket_descriptor, buf, sizeof(buf) - 1, 0);
        }

        seg = buf;
        memset(buf, 0, sizeof(buf));
        full_recv += seg;
    }
    if (debug) {
        size_t n = 20;
        if (full_recv.size() <= n) {
            n = full_recv.size() - 1;
        }
        logger->debug("-> {}", full_recv.substr(full_recv.length() - n));
    }
    return full_recv;
}

string Pop3socket::_recv(){
    char buf[512]{};
    while (true) {
        if (_is_encrypted) {
            gnutls_record_recv(_sess, buf, sizeof(buf) - 1);
        } else {
            recv(_socket_descriptor, buf, sizeof(buf) - 1, 0);
        }
        if (strlen(buf) != 0){ break; }
    }
    string ret_recv = buf;
    logger->debug("-> {}", ret_recv.substr(0, ret_recv.size() - 2));
    return ret_recv;

}

int Pop3socket::_send(string msg){
    msg += "\r\n";
    const char *data = msg.c_str();
    unsigned int strlen = msg.length();
    int status{};
    if(_is_encrypted){
        status = gnutls_record_send(_sess, data, strlen);
    } else {
        status = send(_socket_descriptor, data, strlen, 0);
    }
    if(status >= 0) {
        logger->debug("<- {}", msg.substr(0, msg.size() - 2));
        return SUCCESS; 
    }
    return SEND_ERR;
}

Pop3socket::~Pop3socket() {
    if(_is_encrypted){
        gnutls_bye(_sess, GNUTLS_SHUT_RDWR);
    }

    shutdown(_socket_descriptor, SHUT_RDWR);
    close(_socket_descriptor);

    if(_is_encrypted){
        gnutls_deinit(_sess);
        gnutls_certificate_free_credentials(_xcred);
        gnutls_global_deinit();
    }
}
