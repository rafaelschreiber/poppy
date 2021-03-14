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
    Pop3socket pop3sess{};

public:
    Mailbox(string hostname, uint16_t port, string user, string pass, bool encrypted);
};

#endif // MAILBOX_H