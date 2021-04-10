#!/usr/bin/env bash
# dont run this file directly it's getting executed by meson build

: '
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: compile_javascript_frontend.sh
 * Date: 08-04-2021    
'

set -e

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cd $SCRIPTPATH

# install npm dependencies
npm install

# compile javascript
npm run compile
