/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.h
 * Date: 09-03-2021
 */

#ifndef MAILBOX_H
#define MAILBOX_H

#define DEBUG true

#include <string>
#include "pop3socket.h"

using namespace std;

class Mailbox {
private:
    vector<mail_t> _mail_list;
    uint32_t _mailbox_size{0};
    int _uidl_to_mailid(string uidl);

public:
    Pop3socket pop3sess{};
    Mailbox(string hostname, uint16_t port, string user, string pass, bool encrypted);
    int update_maillist();
    size_t get_mailbox_count() { return _mail_list.size(); }
    uint32_t get_mailbox_size() { return _mailbox_size; }
    int complete_mail_metadata(size_t pos, size_t len);
    mail_t get_email(size_t pos);
    int delete_mail(string uidl);
    int resetMailbox();
    int download_mail(string uidl, string *mail_content);
};

#endif // MAILBOX_H
