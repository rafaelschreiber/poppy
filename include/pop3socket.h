/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: pop3socket.h
 * Date: 28-02-2021
 */

#ifndef POP3SOCKET_H
#define POP3SOCKET_H

#include <string>

#include <netinet/in.h>
#include <gnutls/gnutls.h>

#define SUCCESS 0
#define RESOLV_ERR 1
#define SOCKET_ERR 2
#define TLS_HANDSHAKE_ERR 3
#define PROTOCOL_ERR 4
#define SEND_ERR 5
#define NOT_CONNECTED_ERR 6
#define ALREADY_LOGGED_IN_ERR 7
#define WRONG_CREDENTIALS_ERR 8
#define NOT_LOGGED_IN_ERR 9

using namespace std;


struct mail_t{
    string uidl;
    string sender;
    string subject;
    unsigned int id;
};

struct stat_t{
    unsigned int mails;
    unsigned int bytes;
};

class Pop3socket {
private:
    string _hostname{};
    string _ip_addr{};
    u_int16_t _port{};
    int _addr_family{};
    int _socket_descriptor{};
    struct sockaddr_in _socket_address;
    bool _is_encrypted{};
    bool _session_up{false};
    bool _is_logged_in{false};
    bool _debug_on{false};
    gnutls_session_t _sess{};
    gnutls_certificate_credentials_t _xcred{};

    int _create_bsd_socket();
    int _resolve_name();
    int _setup_gnutls();
    int _recv_server_ok();
    string _recv();
    int _send(string msg);

public:
    Pop3socket();
    Pop3socket(string hostname, uint16_t port, bool is_encrypted);
    void fill_endpoint(string hostname, uint16_t port, bool is_encrypted);
    int connect();
    void switch_debug();
    int login(string username, string password);
    bool ping();
    int get_stats(stat_t *status);
    ~Pop3socket();
};


#endif // POP3SOCKET_H
