/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: main.cpp
 * Date: 10-02-2021
 */

#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>
#include <signal.h>

#include <spdlog/spdlog.h>

#include "globals.h"
#include "mailservice.h"

//int main(int argc, char* argv[]) {
int main() {
    if (debug) { logger->set_level(spdlog::level::debug); }
    logger->info("Welcome to POPpy POP3 client");
    StartGrpcServer();
    return 0;
}
