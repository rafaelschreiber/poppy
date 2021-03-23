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
    vector<mail_t> mails;
    pop3mailbox.pop3sess.get_mails(mails);
    for (auto mail : mails){
        cout << mail.sender() << " - " << mail.date() << " - " << mail.subject() << " - " << mail.sender() << " - " << mail.id() << " - " << mail.size() << " - " << mail.get_header("X-Mailer") << endl;
    }
    return 0;
}
