/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.cpp
 * Date: 09-03-2021
 */

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>

#include "pop3socket.h"
#include "globals.h"

#include "mailbox.h"

using namespace std;

int Mailbox::connect_mailbox(string hostname, uint16_t port, string user, string pass, bool encrypted){
    _pop3sess.fill_endpoint(hostname, port, encrypted);
    int connect_status = _pop3sess.connect();
    if (connect_status != SUCCESS) {
        logger->error("An error occurred while connecting to {}:{}", hostname, port);
        return connect_status;
    }

    int login_status = _pop3sess.login(user, pass);
    if (login_status != SUCCESS) {
        logger->error("An error occurred during authentication on {} at {}:{}", user, hostname, port); 
        return login_status;
    }
    update_maillist();
    return SUCCESS;
}


int Mailbox::update_maillist() {
    vector<mail_t> new_mails_list;
    int status = _pop3sess.get_mails(new_mails_list);
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
            int status = _pop3sess.complete_mail(mail_ptr);
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

int Mailbox::_uidl_to_mailid(string uidl){
    for (size_t i = 0; i < _mail_list.size(); i++) {
        if (_mail_list.at(i).uidl() == uidl){
            return _mail_list.at(i).id();
        }
    }
    return -1;
}


int Mailbox::reset_mailbox() {
    int status = _pop3sess.reset_mailbox();
    return status;
}


int Mailbox::delete_mail(string uidl){
    int mailid = _uidl_to_mailid(uidl);
    if (mailid == -1){
        return UIDL_NOT_FOUND_ERR;
    }
    int status = _pop3sess.delete_mail(mailid);
    return status;
}


int Mailbox::download_mail(string uidl, string *mail_content){
    int mailid = _uidl_to_mailid(uidl);
    if (mailid == -1){
        return UIDL_NOT_FOUND_ERR;
    }
    int status = _pop3sess.download_mail(mailid, mail_content);
    return status;
}
