/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: globals.h
 * Date: 09-04-2021
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <memory>

#include <spdlog/spdlog.h>

using namespace std;

enum Platform {
    DARWIN,
    LINUX,
    ELSE
};

extern Platform current_platform;
extern shared_ptr<spdlog::logger> logger;
extern bool debug;

#endif // GLOBALS_H
