/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: main.cpp
 * Date: 10-02-2021
 */

#include <iostream>
#include <string>
#include "mailbox.h"

using namespace std;

//int main(int argc, char* argv[]) {
int main() {
    Mailbox pop3mailbox = Mailbox("frontend.backend.works", 995, "mailtest", "abc123", true);
    return 0;
}
