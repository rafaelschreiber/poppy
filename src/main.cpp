/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: main.cpp
 * Date: 10-02-2021
 */

#include "globals.h"
#include "mailservice.h"

#include <spdlog/spdlog.h>
#include <CLI11.hpp>
#include <subprocess.hpp>

#include <thread>
#include <future>
#include <vector>
#include <chrono>
#include <csignal>
#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace subprocess;

pid_t envoy_process_pid{0};
bool sigint_initiated{false};

int start_envoy_proxy() {
    auto envoy_process = Popen({"envoy", "-c", 
        prefix + "/share/poppy/envoy_poppy_proxy.yaml", "--log-path", 
        "/tmp/envoy_poppy.log.txt"}, input{PIPE}, output{"/dev/null"});
    envoy_process_pid = envoy_process.pid();
    logger->debug("Envoy proxy started with pid: {}", envoy_process_pid);
    logger->debug("Check envoy log file after exit " 
        "under /tmp/envoy_poppy.log.txt");
    logger->debug("You can also access the envoy admin " 
                    "panel under http://localhost:42963");
    size_t envoy_exit_status = envoy_process.wait();

    if (envoy_exit_status != SUCCESS) {
        logger->warn("Envoy proxy (PID: {}) exited with status code: {}",
            envoy_process_pid, envoy_exit_status);
        envoy_error = true;
    } else {
        logger->debug("Envoy proxy (PID: {}) exited with status code: {}",
            envoy_process_pid, envoy_exit_status);
    }
    return envoy_exit_status;
}


int startup_routine() {
    vector<future<int>*> future_vector;
    future<int> status_grpc_server = async(launch::async, start_grpc_server);
    future_vector.push_back(&status_grpc_server);
    future<int> status_envoy_proxy = async(launch::async, start_envoy_proxy);
    future_vector.push_back(&status_envoy_proxy);
    
    size_t elems = future_vector.size();
    size_t index = 0;
    int returncode;
    future_status status;
    while (true) { // check periodically if one service in vector has exited
        if (index % elems == 0) index = 0;
        status = future_vector.at(index)->wait_for(chrono::seconds(1));
        if (status == future_status::ready) {
            returncode = future_vector.at(index)->get();
            future_vector.erase(future_vector.begin() + index);
            break;
        }
        index++;
    }

    // if envoy is still running after or sigint initiated
    if (kill(envoy_process_pid, 0) == 0 || sigint_initiated) {
        if (!sigint_initiated) {
            logger->debug("Shutting down envoy proxy "
              "after gRPC service shutdown");
            kill(envoy_process_pid, SIGTERM);
        }
    } else {
        if (!envoy_error) logger->critical("Mandadory envoy proxy" 
          "unexpectedly quitted. Shutting down gRPC service");
        shutdown_initiated = 255;
        returncode = ENVOY_UNEXPECTEDLY_QUIT_ERR;
    }

    // use extern var shutdown_initiated as exit code on runtime exit
    if (shutdown_initiated != 255 && shutdown_initiated != 0)
      returncode = shutdown_initiated;
    return returncode;
}


void signal_handler(int signum) {
    if (sigint_initiated) { // if CTRL+C gets pressed a 2nd time
        logger->info("Force shutdown with SIGKILL");
        kill(getpid(), 9);
    }

    shutdown_initiated = 255;
    if (signum == SIGINT) {
        sigint_initiated = true;
        logger->info("SIGINT recieved. Starting graceful shutdown...");
    } else {
        logger->info("SIGTERM recieved. Starting graceful shutdown...");
    }
}


int main(int argc, char** argv) {
    CLI::App app{"POPpy a simple pop3 client with a minimalistic frontend"};
    
    app.add_option("bookmark", bookmark, "Specify POP3 bookmark")
      ->required();
    app.add_option("-c,--config", config_file_path, "Path to your config file")
      ->check(CLI::ExistingFile);
    app.add_flag("-d,--debug", debug, "Turn on debug mode");

    CLI11_PARSE(app, argc, argv);

    logger->info("Welcome to POPpy POP3 client");
    if (debug) { 
        logger->set_level(spdlog::level::debug);
        logger->info("Debug is enabled and prefix={}", prefix);
    }

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    int status = startup_routine(); // service spawner (blocking)
    if (status != SUCCESS) {
        if (debug) {
            logger->error("Terminating poppy due runtime error. "
              "Read the error trace above for troubleshooting");
        } else {
            logger->error("Terminating poppy due runtime error. "
              "To get an error trace turn on debug mode");
        }
        logger->info("Terminating with exit code {} (ERROR)", status);
        return status;
    }

    logger->info("Terminating with exit code {} (SUCCESS)", status);
    return 0;
}
