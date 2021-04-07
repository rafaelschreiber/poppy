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

#include <google/protobuf/map.h>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "mailbox.h"
#include "pop3client.pb.h"
#include "pop3client.grpc.pb.h"

using namespace grpc;

class MailServiceImpl final : public MailService::Service {
public:
    Mailbox *pop3mailbox;

    MailServiceImpl(string hostname, uint16_t port, string username, string password, bool encrypted){
        pop3mailbox = new Mailbox(hostname, port, username, password, encrypted);
    }

    Status GetMailList(ServerContext* context, const google::protobuf::Empty* request, MailList* reply) override {
        reply->set_length(pop3mailbox->get_mailbox_count());
        reply->set_size(pop3mailbox->get_mailbox_size());

        return Status::OK;
    }

    Status GetMailPreviews(ServerContext* context, const MailPreviewRequest* request, MailPreviewResponse* reply) override {
        if (request->pos() > pop3mailbox->get_mailbox_count()){ return Status(StatusCode::OUT_OF_RANGE, "pos is greater than available emails"); }

        pop3mailbox->complete_mail_metadata(request->pos(), request->len());
        for (size_t i = 0; i < request->len(); i++){
            if (request->pos() + i > pop3mailbox->get_mailbox_count()){ break; }
            mail_t curr_mail = pop3mailbox->get_email(request->pos() + i);
            MailPreview* mail_preview = reply->add_mail_preview();
            mail_preview->set_mailid(curr_mail.id());
            mail_preview->set_size(curr_mail.size());
            mail_preview->set_uidl(curr_mail.uidl());

            // headers require a special treamtment in protobuf -.-
            auto headers_map = mail_preview->mutable_headers();
            for (auto const& [key, val] : curr_mail.headers()){
               (*headers_map)[key] = val; 
            }
        }
        return Status::OK;
    }

    Status UpdateMailList(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Empty* reply) override {
        pop3mailbox->update_maillist();
        return Status::OK;
    }

    ~MailServiceImpl(){
        delete pop3mailbox;
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
    return 0;
}
