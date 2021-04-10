/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.h
 * Date: 09-03-2021
 */

#ifndef MAILBOX_H
#define MAILBOX_H

#include "pop3socket.h"

#include <string>
#include <thread>

class Mailbox {
  private:
    std::vector<mail_t> _mail_list{};
    uint32_t _mailbox_size{0};
    int _uidl_to_mailid(std::string uidl);
    std::string _hostname;
    uint16_t _port;
    std::string _user;
    std::string _pass;
    bool _encrypted;
    std::thread _ping_thread;
    Pop3socket _pop3sess{};
    void _ping_thread_function();
    bool _ping_thread_started{false};

  public:
    Mailbox() {}
    int connect_mailbox(std::string hostname, uint16_t port, std::string user, 
      std::string pass, bool encrypted);
    int update_maillist(bool first_connect=false);
    size_t get_mailbox_count() { return _mail_list.size(); }
    uint32_t get_mailbox_size() { return _mailbox_size; }
    int complete_mail_metadata(size_t pos, size_t len);
    mail_t get_email(size_t pos);
    int delete_mail(std::string uidl);
    int reset_mailbox() { return _pop3sess.reset_mailbox(); }
    int download_mail(std::string uidl, std::string* mail_content);
    int reconnect();
    int log_out() { return _pop3sess.log_out(); }
    void close_session();
    ~Mailbox() {}
};

#endif // MAILBOX_H
