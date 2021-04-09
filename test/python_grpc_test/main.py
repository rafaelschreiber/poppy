#!/usr/bin/env python3

import grpc
import poppy_pb2
import poppy_pb2_grpc

def mailservice_getmaillist(stub):
    response = stub.GetMailList(poppy_pb2.google_dot_protobuf_dot_empty__pb2.Empty())
    print(response.size)
    print(response.length)

def mailservice_getmailpreviews(stub):
    request = poppy_pb2.MailPreviewRequest(pos=0, len=20)
    response = stub.GetMailPreviews(request)
    for mail in response.mail_preview:
        print(mail.headers["Subject"])


def main():
    with grpc.insecure_channel('localhost:42962') as channel:
        stub = poppy_pb2_grpc.MailServiceStub(channel)
        mailservice_getmaillist(stub)
        mailservice_getmailpreviews(stub)
        channel.close()

if __name__ == "__main__":
    main()
