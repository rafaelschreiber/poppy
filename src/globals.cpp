/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: globals.cpp
 * Date: 09-04-2021
 */

#include "globals.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include <string>
#include <memory>

using namespace std;

#if __APPLE__
    Platform current_platform = DARWIN;
#elif __linux__
    Platform current_platform = LINUX;
#else
     Platform current_platform = ELSE;
#endif

string prefix = __PREFIX__; // compiler macro for installation prefix
shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("poppy");
bool debug = true;
int shutdown_initiated = 0; // indicator if shutdown procedure started
bool envoy_error = false; // true if envoy crashes
