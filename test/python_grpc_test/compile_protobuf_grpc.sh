#!/usr/bin/env bash

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $SCRIPTPATH

python -m grpc_tools.protoc -I../../protos --python_out=. --grpc_python_out=. ../../protos/pop3client.proto
