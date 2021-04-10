#!/usr/bin/env bash
# dont run this file directly it's getting executed by meson build
set -e

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $SCRIPTPATH

# install npm dependencies
npm install

# compile javascript
npm run compile
