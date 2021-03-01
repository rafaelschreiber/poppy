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
    Pop3socket pop3sess = Pop3socket("mail.privateemail.com", 110, false);
    cout << pop3sess.connect() << endl;
    return 0;
}
