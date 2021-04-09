/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: mailservice.h
 * Date: 09-04-2021
 */

#ifndef MAILSERVICE_H
#define MAILSERVICE_H

#include "mailbox.h"
#include "poppy.pb.h"
#include "poppy.grpc.pb.h"

using namespace grpc;

class MailServiceImpl final : public MailService::Service {
private:
    Mailbox *_pop3mailbox;
    string _account;

public:
    MailServiceImpl(string hostname, uint16_t port, string username, string password, bool encrypted);
    Status GetMailBoxInfo(ServerContext* context, const Empty* request, MailBoxInfo* reply) override;
    Status GetMailPreviews(ServerContext* context, const MailPreviewRequest* request, MailPreviewResponse* reply) override;
    Status UpdateMailbox(ServerContext* context, const Empty* request, StatusResponse* reply) override;
    Status DeleteMail(ServerContext* context, const SpecifiedMail* request, StatusResponse* reply) override;
    Status ResetMailbox(ServerContext* context, const Empty* request, StatusResponse* reply) override;
    Status DownloadMail(ServerContext* context, const SpecifiedMail* request, DownloadedMail* reply) override;
    Status ExitApplication(ServerContext* context, const Empty* request, Empty* reply) override;
    ~MailServiceImpl();

};

void StartGrpcServer();

#endif // MAILSERVICE_H