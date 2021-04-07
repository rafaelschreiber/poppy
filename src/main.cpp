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

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "mailbox.h"
#include "pop3client.pb.h"
#include "pop3client.grpc.pb.h"


class MailServiceImpl final : public MailService::Service {
public:
    Mailbox *pop3mailbox;

    MailServiceImpl(string hostname, uint16_t port, string username, string password, bool encrypted){
        pop3mailbox = new Mailbox(hostname, port, username, password, encrypted);
    }


};

void RunServer(){
    string server_address = "127.0.0.1:50051";
    MailServiceImpl service = MailServiceImpl("frontend.backend.works", 995, "mailtest", "abc123", true);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    cout << "Server started and listening on " << server_address << endl;
    server->Wait();
}

//int main(int argc, char* argv[]) {
int main() {
    RunServer();
    /*
    Mailbox pop3mailbox = Mailbox("frontend.backend.works", 995, "mailtest", "abc123", true);
    vector<mail_t> mails;
    pop3mailbox.print_mails();
    */
    return 0;
}
