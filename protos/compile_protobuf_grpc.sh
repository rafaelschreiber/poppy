#!/usr/bin/env bash
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` pop3client.proto
protoc --cpp_out=. pop3client.proto

cp pop3client.pb.h ../include/pop3client.pb.h
cp pop3client.grpc.pb.h ../include/pop3client.grpc.pb.h

cp pop3client.pb.cc ../src/pop3client.pb.cc
cp pop3client.grpc.pb.cc ../src/pop3client.grpc.pb.cc

rm *.pb.*
