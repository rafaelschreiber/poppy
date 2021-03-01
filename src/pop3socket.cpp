/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: pop3socket.cpp
 * Date: 28-02-2021
 */

#include <iostream>
#include <string>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <gnutls/gnutls.h>

#include "pop3socket.h"

using namespace std;

Pop3socket::Pop3socket(std::string hostname, uint16_t port, bool is_encrypted) {
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
    cout << gnutls_session_get_desc(_sess) << endl;
    int ret = (err_handshake == 0) ? SUCCESS : TLS_HANDSHAKE_ERR;
    return ret;
}

int Pop3socket::connect() {
    char buf[1025]{};

    int ret_resolv = _resolve_name();
    if(ret_resolv != 0){ return ret_resolv; }

    int ret_socket = _create_bsd_socket();
    if(ret_socket != 0){ return ret_socket; }

    if (_is_encrypted){
        int ret_gnutls = _setup_gnutls();
        if(ret_gnutls != 0){ return ret_gnutls; }
    }

    if(_recv().substr(0, 3) == "+OK"){
        return SUCCESS;
    } else {
        return PROTOCOL_ERR;
    }
}

string Pop3socket::_recv(){
    char buf[8193]{};
    if(_is_encrypted){
        gnutls_record_recv(_sess, buf, sizeof(buf) - 1);
    } else {
        recv(_socket_descriptor, buf, sizeof(buf) - 1, 0);
    }
    string ret_recv = buf;
    return ret_recv;

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