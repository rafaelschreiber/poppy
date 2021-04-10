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

using namespace std;

class mail_t {
private:
    string _uidl{};
    map<string, string> _headers{};
    uint16_t _id{};
    uint32_t _size{};

public:
    mail_t(uint16_t id, uint32_t size) { 
        _id = id;
        _size = size;
    }

    mail_t() { }
    
    uint16_t id() { return _id; }
    void id(uint16_t id) { _id = id; }

    string uidl() { return _uidl; }
    void uidl(string uidl) { _uidl = uidl; }
    
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
    gnutls_session_t _sess{};
    gnutls_certificate_credentials_t _xcred{};

    int _create_bsd_socket();
    int _resolve_name();
    int _setup_gnutls();
    int _recv_server_ok();
    string _recv();
    string _recv_to_end();
    int _send(string msg);
    map<string, string> _get_headers(uint16_t mailid);
    string _get_uidl(uint16_t mailid);


public:
    Pop3socket();
    Pop3socket(string hostname, uint16_t port, bool is_encrypted);
    void fill_endpoint(string hostname, uint16_t port, bool is_encrypted);
    int get_mails(vector<mail_t> &mails);
    int connect();
    int login(string username, string password);
    int complete_mail(mail_t *mail);
    bool ping();
    int get_stats(stat_t *status);
    int reset_mailbox();
    int delete_mail(uint16_t mailid);
    int download_mail(uint16_t mailid, string *mail_content);
    ~Pop3socket();
};


#endif // POP3SOCKET_H
