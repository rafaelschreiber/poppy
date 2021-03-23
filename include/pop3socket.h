/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: pop3socket.h
 * Date: 28-02-2021
 */

#ifndef POP3SOCKET_H
#define POP3SOCKET_H

#include <string>
#include <vector>
#include <map>

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

/*
 * Ich liebe nicht standartisierte Datestrings :))
 * Date: Tue,  9 Mar 2021 22:17:58 +0100 (CET) # postfix ubuntu
 * Date: 8 Jan 2020 03:31:07 -0500 # fortimail
 * Date: Sat, 18 Jun 2016 16:45:44 +0000 # Google Mail
 */

class mail_t {
private:
    string _uidl{};
    map<string, string> _headers{};
    uint16_t _id{};
    uint32_t _size{};

public:
    mail_t(uint16_t id, uint32_t size, string uidl, map<string, string> headers) { 
        _id = id;
        _size = size;
        _uidl = uidl;
        _headers = headers;
    }

    mail_t() { }
    
    uint16_t id() { return _id; }
    void id(uint16_t id) { _id = id; }

    string uidl() { return _uidl; }
    void id(string uidl) { _uidl = uidl; }
    
    uint16_t size() { return _size; }
    void size(uint32_t size) { _size = size; }

    map<string, string> headers() { return _headers; }
    void headers(map<string, string> headers) { _headers = headers; }

    string subject() { return _headers["Subject"]; }
    string date() { return _headers["Date"]; }
    string sender() { return _headers["From"]; }
    string recipient() { return _headers["To"]; }

    string get_header(string key) { return _headers[key]; }

    ~mail_t() { }
};

struct stat_t{
    uint16_t mails;
    uint32_t bytes;
};

class Pop3socket {
private:
    string _hostname{};
    string _ip_addr{};
    uint16_t _port{};
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
    string _recv_to_end();
    int _send(string msg);
    map<string, string> _get_header(uint16_t mailid);
    string _get_uidl(uint16_t mailid);


public:
    Pop3socket();
    Pop3socket(string hostname, uint16_t port, bool is_encrypted);
    void fill_endpoint(string hostname, uint16_t port, bool is_encrypted);
    int get_mails(vector<mail_t> &mails);
    int connect();
    void switch_debug();
    int login(string username, string password);
    bool ping();
    int get_stats(stat_t *status);
    ~Pop3socket();
};


#endif // POP3SOCKET_H
