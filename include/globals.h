/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: globals.h
 * Date: 09-04-2021
 */

#ifndef GLOBALS_H
#define GLOBALS_H

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
#define ENVOY_UNEXPECTEDLY_QUIT_ERR 11
#define RECONNECT_ERR 12
#define NON_NETWORK_ERR 255 // not used as return code just internally

#include <spdlog/spdlog.h>

#include <string>
#include <memory>

enum Platform {
    DARWIN = 1,
    LINUX = 2,
    ELSE = 3
};

extern std::string prefix;
extern Platform current_platform;
extern std::shared_ptr<spdlog::logger> logger;
extern bool debug;
extern int shutdown_initiated;
extern bool envoy_error;

#endif // GLOBALS_H
