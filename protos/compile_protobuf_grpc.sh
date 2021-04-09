#!/usr/bin/env bash
# dont run this file directly it's getting executed by meson build

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $SCRIPTPATH

# compile protobuf & grpc files for c++ backend
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` poppy.proto
protoc --cpp_out=. poppy.proto

# compile protobuf & grpc files for javascript frontend
protoc poppy.proto --js_out=import_style=commonjs:.
protoc poppy.proto --grpc-web_out=import_style=commonjs,mode=grpcwebtext:.

# copy .h files to include/
cp poppy.pb.h ../include/poppy.pb.h
cp poppy.grpc.pb.h ../include/poppy.grpc.pb.h

# copy .cc files to src/
cp poppy.pb.cc ../src/poppy.pb.cc
cp poppy.grpc.pb.cc ../src/poppy.grpc.pb.cc

# copy .js files to frontend/js/
cp poppy_pb.js ../frontend/js/poppy_pb.js
cp poppy_grpc_web_pb.js ../frontend/js/poppy_grpc_web_pb.js

# remove all generated protobuf & grpc files from source location
rm *.pb.*
rm *_pb.*

