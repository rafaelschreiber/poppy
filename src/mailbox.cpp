/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.cpp
 * Date: 09-03-2021
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <tabulate.hpp>

#include "pop3socket.h"
#include "mailbox.h"

using namespace std;
using namespace tabulate;

Mailbox::Mailbox(string hostname, uint16_t port, string user, string pass, bool encrypted){
    std::ostringstream oss;
    pop3sess.fill_endpoint(hostname, port, encrypted);
    if (DEBUG) { pop3sess.switch_debug(); }
    int connect_status = pop3sess.connect();
    if (connect_status != 0){
        oss << "PROTOCOL_ERR: Cannot connect to server " << hostname << ":" << port << endl;
        throw oss.str();
    }

    int login_status = pop3sess.login(user, pass);
    if (login_status != 0){
        switch (login_status) {
            case PROTOCOL_ERR:
                oss << "PROTOCOL_ERR: Login protocol not satisfied" << endl;
                throw oss.str();
            case WRONG_CREDENTIALS_ERR:
                oss << "WRONG_CREDENTIALS_ERR: Wrong credentials for user " << user << " specified" << endl;
                throw oss.str();
        }
    }
    update_maillist();
}


int Mailbox::update_maillist() {
    vector<mail_t> new_mails_list;
    int status = pop3sess.get_mails(new_mails_list);
    if (status != SUCCESS) { return status; }
    reverse(_mail_list.begin(), _mail_list.end());
    
    size_t new_mails_count = new_mails_list.size();
    size_t new_mails_added = new_mails_count - _mail_list.size();

    for (size_t i = 0; i < new_mails_added; i++){
        mail_t new_mail = new_mails_list.at(new_mails_count - new_mails_added + i);
        _mailbox_size += new_mail.size();
        _mail_list.push_back(new_mail);
    }

    mail_t *mail_ptr = _mail_list.data();
    for (size_t i = 1; i <= new_mails_count; i++) {
        mail_ptr->id(i);
        mail_ptr++;
    }

    reverse(_mail_list.begin(), _mail_list.end());
    return SUCCESS;
}

int Mailbox::complete_mail_metadata(size_t pos, size_t len) {
    mail_t *mail_ptr = _mail_list.data();
    mail_ptr += pos;
    for (size_t i = 0; i < len; i++){
        if (mail_ptr == nullptr) { break; }
        if (mail_ptr->uidl().length() == 0) {
            int status = pop3sess.complete_mail(mail_ptr);
            if (status != SUCCESS) { return status; }
        }
        mail_ptr++;
    }
    return SUCCESS;
}

mail_t Mailbox::get_email(size_t pos){
    if (pos + 1 > _mail_list.size()) { return mail_t(); }
    return _mail_list.at(pos);
}
