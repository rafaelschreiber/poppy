/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailservice.cpp
 * Date: 09-04-2021
 */

#include <grpcpp/server_builder.h>

#include "mailbox.h"
#include "poppy.pb.h"
#include "poppy.grpc.pb.h"
#include "globals.h"

#include "mailservice.h"

using namespace grpc;

MailServiceImpl::MailServiceImpl(string hostname, uint16_t port, string username, string password, bool encrypted){
    _pop3mailbox = new Mailbox(hostname, port, username, password, encrypted);
    _account = username;
    logger->info("New pop3 mailbox created for {} on {}:{}", username, hostname, port);
}

Status MailServiceImpl::GetMailBoxInfo(ServerContext* context, const Empty* request, MailBoxInfo* reply) {
    reply->set_account(_account);
    reply->set_length(_pop3mailbox->get_mailbox_count());
    reply->set_size(_pop3mailbox->get_mailbox_size());

    return Status::OK;
}

Status MailServiceImpl::GetMailPreviews(ServerContext* context, const MailPreviewRequest* request, MailPreviewResponse* reply) {
    if (request->pos() > _pop3mailbox->get_mailbox_count()){ return Status(StatusCode::OUT_OF_RANGE, "pos is greater than available emails"); }

    _pop3mailbox->complete_mail_metadata(request->pos(), request->len());
    for (size_t i = 0; i < request->len(); i++){
        if (request->pos() + i > _pop3mailbox->get_mailbox_count()){ break; }
        mail_t curr_mail = _pop3mailbox->get_email(request->pos() + i);
        MailPreview* mail_preview = reply->add_mail_preview();
        mail_preview->set_mailid(curr_mail.id());
        mail_preview->set_size(curr_mail.size());
        mail_preview->set_uidl(curr_mail.uidl());

        // maps require a special treamtment in protobuf -.-
        auto headers_map = mail_preview->mutable_headers();
        for (auto const& [key, val] : curr_mail.headers()){
            (*headers_map)[key] = val; 
        }
    }
    return Status::OK;
}

Status MailServiceImpl::UpdateMailbox(ServerContext* context, const Empty* request, StatusResponse* reply) {
    int status = _pop3mailbox->update_maillist();
    if (status != 0) {
        reply->set_success(false);
    } else {
        reply->set_success(true);
    }
    return Status::OK;
}

Status MailServiceImpl::DeleteMail(ServerContext* context, const SpecifiedMail* request, StatusResponse* reply) {
    int status = _pop3mailbox->delete_mail(request->uidl());
    if (status != 0) {
        reply->set_success(false);
    } else {
        reply->set_success(true);
    }
    return Status::OK;        
}

Status MailServiceImpl::ResetMailbox(ServerContext* context, const Empty* request, StatusResponse* reply) {
    int status = _pop3mailbox->resetMailbox();
    if (status != 0) {
        reply->set_success(false);
    } else {
        reply->set_success(true);
    }
    return Status::OK;        
}

Status MailServiceImpl::DownloadMail(ServerContext* context, const SpecifiedMail* request, DownloadedMail* reply) {
    string mail_content{};
    int status = _pop3mailbox->download_mail(request->uidl(), &mail_content);
    if (status != 0) {
        reply->set_success(false);
    } else {
        reply->set_success(true);
    }
    reply->set_mailcontent(mail_content);
    return Status::OK;
}

Status MailServiceImpl::ExitApplication(ServerContext* context, const Empty* request, Empty* reply) {
    cout << "servus" << endl;
    return Status::OK;
}

MailServiceImpl::~MailServiceImpl(){
    delete _pop3mailbox;
}

void StartGrpcServer() {
    logger->info("Starting gRPC service for poppy frontend");
    string server_address = "127.0.0.1:42962";
    MailServiceImpl service = MailServiceImpl("mail.privateemail.com", 995, "rafael@backend.works", "*VFg#xfm7$cbvXW9T%FY", true);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    logger->info("gRPC server successfully started and is now listening on: {}", server_address);
    server->Wait();
}
