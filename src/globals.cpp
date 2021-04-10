/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: globals.cpp
 * Date: 09-04-2021
 */

#include <string>
#include <memory>

#include <spdlog/sinks/stdout_color_sinks.h>

#include "globals.h"

using namespace std;

#if __APPLE__
    Platform current_platform = DARWIN;
#elif __linux__
    Platform current_platform = LINUX;
#else
     Platform current_platform = ELSE;
#endif

shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("poppy");
bool debug = true;
string prefix = __PREFIX__;
