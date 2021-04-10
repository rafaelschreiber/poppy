/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.cpp
 * Date: 09-03-2021
 */

#include "globals.h"
#include "pop3socket.h"
#include "mailbox.h"

#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

int Mailbox::connect_mailbox(string hostname, uint16_t port, string user, 
  string pass, bool encrypted) {
    _hostname = hostname;
    _port = port;
    _user = user;
    _pass = pass;
    _encrypted = encrypted;

    _pop3sess.fill_endpoint(hostname, port, encrypted);
    int connect_status = _pop3sess.connect();
    if (connect_status != SUCCESS) {
        logger->error("An error occurred while connecting to {}:{}", hostname, 
          port);
        return connect_status;
    }

    int login_status = _pop3sess.login(user, pass);
    if (login_status != SUCCESS) {
        logger->error("An error occurred during authentication on {} at {}:{}", 
          user, hostname, port); 
        return login_status;
    }

    // background thread to avoid disconnect due inactivity
    if (!_ping_thread_started) {
        _ping_thread = thread(&Mailbox::_ping_thread_function, this);
        _ping_thread_started = true;
        logger->debug("Background ping thread started");
    }

    return SUCCESS;
}


int Mailbox::update_maillist(bool first_connect) {
    if (!first_connect) { // fetching new emails require a full reconnect
        int status = reconnect();
        if (status != SUCCESS) {
            logger->error("Reconnect failed initiating shutdown...");
            return status; 
        }
    }

    _mail_list.clear();
    int status = _pop3sess.get_mails(_mail_list);
    if (status != SUCCESS) {
        logger->error("Cannot retrieve mail list");
        return status; 
    }

    // calculate mailbox storage size
    for (size_t i = 0; i < _mail_list.size(); i++) {
        mail_t new_mail = _mail_list.at(i);
        _mailbox_size += new_mail.size();
    }
    
    // sort by newest mail
    reverse(_mail_list.begin(), _mail_list.end());
    return SUCCESS;
}


int Mailbox::complete_mail_metadata(size_t pos, size_t len) {
    mail_t* mail_ptr = _mail_list.data();
    mail_ptr += pos;

    for (size_t i = 1; i <= len; i++) {
        if (mail_ptr->id() <= 0) break;
        if (mail_ptr->uidl().length() == 0) {
            int status = _pop3sess.complete_mail(mail_ptr);
            if (status != SUCCESS) { return status; }
        }
        mail_ptr++;
    }
    return SUCCESS;
}


mail_t Mailbox::get_email(size_t pos) {
    if (pos + 1 > _mail_list.size()) return mail_t();
    return _mail_list.at(pos);
}


int Mailbox::_uidl_to_mailid(string uidl) {
    for (size_t i = 0; i < _mail_list.size(); i++) {
        if (_mail_list.at(i).uidl() == uidl) return _mail_list.at(i).id();
    }
    logger->warn("UIDL: {} not found", uidl);
    return -1;
}


int Mailbox::delete_mail(string uidl) {
    int mailid = _uidl_to_mailid(uidl);
    if (mailid == -1) return UIDL_NOT_FOUND_ERR;
    int status = _pop3sess.delete_mail(mailid);
    return status;
}


int Mailbox::download_mail(string uidl, string* mail_content) {
    int mailid = _uidl_to_mailid(uidl);
    if (mailid == -1) return UIDL_NOT_FOUND_ERR;
    int status = _pop3sess.download_mail(mailid, mail_content);
    return status;
}


int Mailbox::reconnect() {
    _pop3sess.close_session(true);
    logger->debug("Trying reconnecting to: {} at {}:{}...", _user, 
      _hostname, _port);
    int status = connect_mailbox(_hostname, _port, _user, _pass, _encrypted);
    return status;
}


void Mailbox::_ping_thread_function() {
    int noop_status;
    this_thread::sleep_for(10000ms);

    while (!shutdown_initiated) {
        if (_pop3sess.in_update_state()) {
            noop_status = _pop3sess.ping();
            if (noop_status != SUCCESS) break;
        }
        this_thread::sleep_for(10000ms);
    }

    if (!shutdown_initiated) {
        logger->error("Connection timeout. Server is not reachable. "
          "Initiating shutdown...");
        shutdown_initiated = noop_status;
    }
}


void Mailbox::close_session() {
    _mail_list.clear();
    _pop3sess.close_session();
}
