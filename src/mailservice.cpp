/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailservice.cpp
 * Date: 09-04-2021
 */

#include "globals.h"
#include "mailbox.h"
#include "mailservice.h"

#include "poppy.pb.h"
#include "poppy.grpc.pb.h"

#include <grpcpp/server_builder.h>

#include <thread>
#include <exception>
#include <stdlib.h>

using namespace std;
using namespace grpc;

unique_ptr<grpc::Server> server; // pointer to grpc server

int MailServiceImpl::ConnectMailService(string hostname, uint16_t port, 
  string username, string password, bool encrypted){
    
    int status = _pop3mailbox.connect_mailbox(hostname, port, username, 
      password, encrypted);
    if (status != SUCCESS) {
        logger->error("An error occurred during mailbox initialization");
        return status;
    }
    _account = username;
    logger->info("New pop3 mailbox created for {} on {}:{}", username, 
      hostname, port);
    status = _pop3mailbox.update_maillist(true);
    return status;
}


Status MailServiceImpl::GetMailBoxInfo(ServerContext* context, 
  const Empty* request, MailBoxInfo* reply) {
    
    logger->debug("GetMailBoxInfo() called by: {}", context->peer());
    reply->set_account(_account);
    reply->set_length(_pop3mailbox.get_mailbox_count());
    reply->set_size(_pop3mailbox.get_mailbox_size());
    return Status::OK;
}


Status MailServiceImpl::GetMailPreviews(ServerContext* context, 
  const MailPreviewRequest* request, MailPreviewResponse* reply) {
    
    logger->debug("GetMailPreviews(pos={}, len={}) called by: {}", 
      request->pos(), request->len(), context->peer());
    
    if (request->pos() > _pop3mailbox.get_mailbox_count()){ 
        return Status(StatusCode::OUT_OF_RANGE, 
          "pos is greater than available emails"); 
    }

    if (_pop3mailbox.get_mailbox_count() == 0) return Status::OK;
    int status = _pop3mailbox.complete_mail_metadata(request->pos(), 
      request->len());

    if (status != SUCCESS) {
        logger->error("An error occurred while recieving mail metadata");
        shutdown_initiated = status;
        return Status::OK;
    }

    for (size_t i = 0; i < request->len(); i++){
        if (request->pos() + i > _pop3mailbox.get_mailbox_count()) break;
        mail_t curr_mail = _pop3mailbox.get_email(request->pos() + i);
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


Status MailServiceImpl::UpdateMailbox(ServerContext* context, 
  const Empty* request, StatusResponse* reply) {
    
    logger->debug("UpdateMailbox() called by: {}", context->peer());
    int status = _pop3mailbox.update_maillist();
    if (status != 0) {
        reply->set_success(false);
        shutdown_initiated = status;
    } else {
        reply->set_success(true);
    }
    return Status::OK;
}


Status MailServiceImpl::DeleteMail(ServerContext* context, 
  const SpecifiedMail* request, StatusResponse* reply) {
    
    logger->debug("DeleteMail(uidl={}) called by: {}", 
      request->uidl(), context->peer());
    
    int status = _pop3mailbox.delete_mail(request->uidl());
    if (status != 0) {
        reply->set_success(false);
        logger->error("An error occurred while deleteing mail with uidl: {}", 
          request->uidl());
        shutdown_initiated = status;
    } else {
        reply->set_success(true);
    }
    return Status::OK;        
}


Status MailServiceImpl::ResetMailbox(ServerContext* context, 
  const Empty* request, StatusResponse* reply) {
    
    logger->debug("ResetMailbox called by: {}", context->peer());
    int status = _pop3mailbox.reset_mailbox();
    if (status != 0) {
        reply->set_success(false);
        logger->error("An error occurred while resetting mailbox");
        shutdown_initiated = status;
    } else {
        reply->set_success(true);
    }
    return Status::OK;        
}


Status MailServiceImpl::DownloadMail(ServerContext* context, 
  const SpecifiedMail* request, DownloadedMail* reply) {
    
    logger->debug("DownloadMail(uidl={}) called by: {}", request->uidl(), 
      context->peer());

    string mail_content{};
    int status = _pop3mailbox.download_mail(request->uidl(), &mail_content);
    if (status != 0) {
        reply->set_success(false);
        logger->error("An error occurred while downloading mail with uidl: {}", 
          request->uidl());
        shutdown_initiated = status;
    } else {
        reply->set_success(true);
    }

    reply->set_mailcontent(mail_content);
    return Status::OK;
}


Status MailServiceImpl::ExitApplication(ServerContext* context, 
  const Empty* request, StatusResponse* reply) {

    logger->debug("ExitApplication called by: {}", context->peer());
    int status = _pop3mailbox.log_out();
    if (status != SUCCESS) {
        logger->warn("Properly log-out failed. Mails marked for deletion are "
          "not deleted");
        reply->set_success(false);
    } else {
        reply->set_success(true);
    }

    shutdown_initiated = 255;
    return Status::OK;
}


void MailServiceImpl::ExitMailService() {
    _pop3mailbox.close_session();
    logger->info("Successfully quitted pop3 session");
}


void check_shutdown(){
    while (!shutdown_initiated) {
        this_thread::sleep_for(1000ms);
    }
    logger->info("gRPC server successfully shut down");
    server->Shutdown();
}


int open_frontend() {
    string open_command;
    if (current_platform == 1) {
        open_command = "open " + prefix + "/share/poppy/index.html";
    } else {
        open_command = "xdg-open " + prefix + "/share/poppy/index.html";
    }
    logger->debug("Trying to open frontend with command: {}", open_command);
    return system(open_command.c_str());
}


int start_grpc_server() {
    logger->info("Starting gRPC service for poppy frontend");
    string server_addr = "127.0.0.1:42962";
    MailServiceImpl* service = new MailServiceImpl();
    
    this_thread::sleep_for(1000ms); // wait for envoy to start up
    if (envoy_error) {
        logger->critical("Envoy failed to start up. Aborting startup");
        free(service);
        return ENVOY_UNEXPECTEDLY_QUIT_ERR; 
    }

    int status = service->ConnectMailService("frontend.backend.works", 995, 
      "mailtest", "abc123", true);
    if (status != SUCCESS){
        logger->error("An error occurred while starting the gRPC service");
        free(service);
        return status;
    }
    
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    builder.RegisterService(service);
    server = builder.BuildAndStart();
    logger->info("gRPC server successfully started and is now "
      "listening on: {}", server_addr);
    thread check_shutdown_thread(check_shutdown);
    
    if (open_frontend() != SUCCESS) { 
        logger->warn("Failed to start frontend. Please open the html file "
          "manually located under: {}/share/poppy/index.html", prefix); 
    }

    server->Wait();
    check_shutdown_thread.join();
    service->ExitMailService();
    server->Shutdown();
    free(service);
    return SUCCESS;
}
