/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: globals.h
 * Date: 09-04-2021
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <memory>

#include <spdlog/spdlog.h>

// defined error codes 
#define SUCCESS 0
#define RESOLV_ERR 1
#define SOCKET_ERR 2
#define TLS_HANDSHAKE_ERR 3
#define PROTOCOL_ERR 4
#define SEND_ERR 5
#define NOT_CONNECTED_ERR 6
#define ALREADY_LOGGED_IN_ERR 7
#define WRONG_CREDENTIALS_ERR 8
#define NOT_LOGGED_IN_ERR 9
#define UIDL_NOT_FOUND_ERR 10

using namespace std;

enum Platform {
    DARWIN,
    LINUX,
    ELSE
};

extern string prefix;
extern Platform current_platform;
extern shared_ptr<spdlog::logger> logger;
extern bool debug;

#endif // GLOBALS_H
