/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailbox.h
 * Date: 09-03-2021
 */

#ifndef MAILBOX_H
#define MAILBOX_H

#define DEBUG false

#include <string>
#include "pop3socket.h"

using namespace std;

class Mailbox {
private:
    

public:
    Pop3socket pop3sess{};
    Mailbox(string hostname, uint16_t port, string user, string pass, bool encrypted);
    void print_mails();

};

#endif // MAILBOX_H
