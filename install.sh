#!/usr/bin/env bash

# don't run this file directly, it will get executed by meson install

# setup output for install log
rm $MESON_BUILD_ROOT/meson-logs/install-log.txt
exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3
exec 1>$MESON_BUILD_ROOT/meson-logs/install-log.txt 2>&1

echo $DESTDIR
echo $MESON_BUILD_ROOT
echo $MESON_SOURCE_ROOT
echo $MESON_INSTALL_PREFIX
