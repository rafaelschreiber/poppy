/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailservice.h
 * Date: 09-04-2021
 */

#ifndef MAILSERVICE_H
#define MAILSERVICE_H

#include "poppy.pb.h"
#include "poppy.grpc.pb.h"
#include "mailbox.h"

class MailServiceImpl final : public MailService::Service {
  private:
    Mailbox _pop3mailbox{};
    std::string _account;

  public:
    MailServiceImpl() {}
    int ConnectMailService(std::string hostname, uint16_t port, 
      std::string username, std::string password, bool encrypted);
    grpc::Status GetMailBoxInfo(grpc::ServerContext* context, 
      const Empty* request, MailBoxInfo* reply) override;
    grpc::Status GetMailPreviews(grpc::ServerContext* context, 
      const MailPreviewRequest* request, MailPreviewResponse* reply) override;
    grpc::Status UpdateMailbox(grpc::ServerContext* context, 
      const Empty* request, StatusResponse* reply) override;
    grpc::Status DeleteMail(grpc::ServerContext* context, 
      const SpecifiedMail* request, StatusResponse* reply) override;
    grpc::Status ResetMailbox(grpc::ServerContext* context, 
      const Empty* request, StatusResponse* reply) override;
    grpc::Status DownloadMail(grpc::ServerContext* context, 
      const SpecifiedMail* request, DownloadedMail* reply) override;
    grpc::Status ExitApplication(grpc::ServerContext* context, 
      const Empty* request, StatusResponse* reply) override;
    void ExitMailService();
    ~MailServiceImpl() {}

};

int start_grpc_server();

#endif // MAILSERVICE_H
