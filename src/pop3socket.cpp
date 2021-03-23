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
    if(resolved_host == nullptr){
        return RESOLV_ERR;
    }
    in_addr **ip_addr_ptr = (struct in_addr **)resolved_host->h_addr_list;
    _addr_family = resolved_host->h_addrtype;
    _ip_addr = inet_ntoa(*ip_addr_ptr[0]);
    return SUCCESS;
}

int Pop3socket::_create_bsd_socket() {
    _socket_descriptor = socket(_addr_family, SOCK_STREAM, 0);
    memset(&_socket_address, '\0', sizeof(_socket_address));
    _socket_address.sin_family = _addr_family;
    _socket_address.sin_port = htons(_port);

    inet_pton(_addr_family, _ip_addr.c_str(), &_socket_address.sin_addr);
    int err = ::connect(_socket_descriptor, (struct sockaddr *) &_socket_address, sizeof(_socket_address));

    int ret = (err == 0) ? SUCCESS : SOCKET_ERR;
    return ret;
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
    if (_debug_on) { cout << gnutls_session_get_desc(_sess) << endl; }
    int ret = (err_handshake == 0) ? SUCCESS : TLS_HANDSHAKE_ERR;
    return ret;
}

int Pop3socket::connect() {
    int ret_resolv = _resolve_name();
    if(ret_resolv != 0){ return ret_resolv; }

    int ret_socket = _create_bsd_socket();
    if(ret_socket != 0){ return ret_socket; }

    if (_is_encrypted){
        int ret_gnutls = _setup_gnutls();
        if(ret_gnutls != 0){ return ret_gnutls; }
    }

    if(_recv().substr(0, 3) == "+OK"){
        _session_up = true;
        return SUCCESS;
    } else {
        return PROTOCOL_ERR;
    }
}

int Pop3socket::login(string username, string password) {
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(_is_logged_in){ return ALREADY_LOGGED_IN_ERR; }
    _send("USER " + username);
    if(_recv().substr(0, 3) == "-ERR") { return PROTOCOL_ERR; }
    _send("PASS " + password);
    string auth_response = _recv();
    if(auth_response.substr(0, 3) == "+OK"){
        _is_logged_in = true;
        return SUCCESS;
    } else if (auth_response.substr(0, 11) == "-ERR [AUTH]"){
        cout << "here" << endl;
        return WRONG_CREDENTIALS_ERR;
    } else {
        return PROTOCOL_ERR;
    }
}

void Pop3socket::switch_debug() {
    _debug_on = _debug_on ? false : true;
}

bool Pop3socket::ping(){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("NOOP");
    string noop_response = _recv();
    if(noop_response.substr(0, 3) == "+OK"){
        return true;
    } else {
        return false;
    }
}

int Pop3socket::get_mails(vector<mail_t> &mails){
    if(!_session_up){ return NOT_CONNECTED_ERR; }
    if(!_is_logged_in){ return NOT_LOGGED_IN_ERR; }
    _send("LIST");
    string list_response = _recv();
    if(list_response.substr(0, 3) != "+OK"){ return PROTOCOL_ERR; }
    vector<string> list_rows;
    vector<string> list_row_data;
    pystring::split(list_response, list_rows, "\n");
    list_rows.erase(list_rows.begin());
    for(string list_row : list_rows){
        list_row_data.clear();

        if (list_row.substr(0, 1) == ".") { break; }

        pystring::split(list_row, list_row_data, " ");

        map<string, string> headers = _get_header(stoi(list_row_data.at(0)));  
        mail_t new_mail(stoi(list_row_data.at(0)), stoi(list_row_data.at(1)), " ", headers);
        mails.push_back(new_mail);
    }

    return SUCCESS;
}

map<string, string> Pop3socket::_get_header(uint16_t mailid){
    _send("TOP " + to_string(mailid) + " 0");
    string headers_response = _recv();
    map<string, string> headers;
    vector<string> headers_rows;
    pystring::split(headers_response, headers_rows, "\r\n");
    headers_rows.erase(headers_rows.begin());

    string key;
    string val;
    for (string headers_row : headers_rows){
        if (headers_row.length() == 0) { break; }
        key.clear();
        val.clear();

        for(char c : headers_row){
            if(c == ':'){ break; }
            key += c;
        }

        val = headers_row.substr(key.length() + 2, string::npos);
        headers[key] = val;
    }

    return headers;
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

string Pop3socket::_recv(){
    char buf[8193]{};
    while (true) {
        if (_is_encrypted) {
            gnutls_record_recv(_sess, buf, sizeof(buf) - 1);
        } else {
            recv(_socket_descriptor, buf, sizeof(buf) - 1, 0);
        }
        if (strlen(buf) != 0){ break; }
    }
    string ret_recv = buf;
    if (_debug_on) { cout << "recv: " << ret_recv << endl; }
    return ret_recv;

}

int Pop3socket::_send(string msg){
    msg += "\r\n";
    const char *data = msg.c_str();
    if (_debug_on) { cout << "send: " << msg << endl; }
    unsigned int strlen = msg.length();
    int status{};
    if(_is_encrypted){
        status = gnutls_record_send(_sess, data, strlen);
    } else {
        status = send(_socket_descriptor, data, strlen, 0);
    }
    if(status >= 0){ return SUCCESS; }
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
