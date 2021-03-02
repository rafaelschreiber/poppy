/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: main.cpp
 * Date: 10-02-2021
 */

#include <iostream>
#include <string>
#include "pop3socket.h"

using namespace std;

//int main(int argc, char* argv[]) {
int main() {
    Pop3socket pop3sess = Pop3socket("mail.mailserver.com", 995, true);
    pop3sess.switch_debug();
    pop3sess.connect();
    pop3sess.login("user@domain.com", "topsecret");
    return 0;
}
