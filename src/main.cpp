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

int startup_routine(){
    int status = start_grpc_server();
    if (status != SUCCESS) { return status; }
    return SUCCESS;
}

int main(int argc, char** argv) {
    logger->info("Welcome to POPpy POP3 client {}", prefix);
    if (debug) { 
        logger->set_level(spdlog::level::debug);
        logger->info("Debug is enabled");
    }
    
    int status = startup_routine();
    if (status != SUCCESS) {
        logger->error("Terminating poppy due connection error. Read error trace above for troubleshooting or turn on debugging");
        logger->info("Terminating with error code {}", status);
        return 1;
    }
    logger->info("Terminating with error code {}", status);
    return 0;
}
