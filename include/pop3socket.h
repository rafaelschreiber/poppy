/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: pop3socket.h
 * Date: 28-02-2021
 */

#ifndef POP3SOCKET_H
#define POP3SOCKET_H

#include <netinet/in.h>
#include <gnutls/gnutls.h>

#include <fstream>
#include <string>
#include <vector>
#include <map>

class mail_t {
  private:
    std::string _uidl{};
    std::map<std::string, std::string> _headers{};
    uint16_t _id{};
    uint32_t _size{};

  public:
    mail_t() {}
    mail_t(uint16_t id, uint32_t size) { _id = id; _size = size; }
    uint16_t id() { return _id; }
    void id(uint16_t id) { _id = id; }
    std::string uidl() { return _uidl; }
    void uidl(std::string uidl) { _uidl = uidl; }
    uint16_t size() { return _size; }
    void size(uint32_t size) { _size = size; }
    std::map<std::string, std::string> headers() { return _headers; }
    void headers(std::map<std::string, std::string> headers) 
      { _headers = headers; }
    std::string subject() { return _headers["Subject"]; }
    std::string date() { return _headers["Date"]; }
    std::string sender() { return _headers["From"]; }
    std::string recipient() { return _headers["To"]; }
    std::string get_header(std::string key) { return _headers[key]; }
    ~mail_t() {}
};

struct stat_t{
    uint16_t mails;
    uint32_t bytes;
};

class Pop3socket {
  private:
    std::string _hostname{};
    std::string _ip_addr{};
    uint16_t _port{};
    int _addr_family{};
    int _socket_descriptor{};
    struct sockaddr_in _socket_address;
    bool _is_encrypted{};
    bool _session_up{false};
    bool _is_logged_in{false};
    std::ofstream _communication_debug_log;
    gnutls_session_t _sess{};
    gnutls_certificate_credentials_t _xcred{};
    int _create_bsd_socket();
    int _resolve_name();
    int _setup_gnutls();
    int _recv_server_ok();
    std::string _recv_short();
    std::string _recv_long();
    std::string _recv(bool islong=false);
    int _send(std::string msg);
    std::map<std::string, std::string> _get_headers(uint16_t mailid);
    std::string _get_uidl(uint16_t mailid);

  public:
    Pop3socket() {}
    void fill_endpoint(std::string hostname, uint16_t port, bool is_encrypted);
    int get_mails(std::vector<mail_t> &mails);
    int connect();
    int login(std::string username, std::string password);
    int complete_mail(mail_t *mail);
    int ping();
    int get_stats(stat_t *status);
    int reset_mailbox();
    int delete_mail(uint16_t mailid);
    int download_mail(uint16_t mailid, std::string *mail_content);
    int log_out();
    bool in_update_state() { return _is_logged_in && _session_up; }
    void close_session(bool reconnect=false);
    ~Pop3socket() {}
};


#endif // POP3SOCKET_H
