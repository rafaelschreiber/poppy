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
}

void Mailbox::print_mails() {
    Table mail_table;
    vector <mail_t> mail_list;
    pop3sess.get_mails(mail_list);

    mail_table.add_row({"Mail ID", "Sender", "Subject", "Date"});

    for (mail_t mail : mail_list) {
        mail_table.add_row({to_string(mail.id()), mail.sender(), mail.subject(), mail.date()});
    }

    mail_table.format()
            .border_top("-")
            .border_bottom("-")
            .border_left("|")
            .border_right("|")
            .corner(".");

    mail_table[0].format()
            .font_color(Color::yellow)
            .font_style({FontStyle::bold});

    cout << mail_table << endl;
}