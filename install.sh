#!/usr/bin/env bash
# dont run this file directly it's getting executed by meson install

: '
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: compile_protobuf_grpc.sh
 * Date: 03-04-2021    
'

# setup output for install log
exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3
exec 1>$MESON_BUILD_ROOT/meson-logs/install-log.txt 2>&1


# create directory structures
mkdir -p $DESTDIR/$MESON_INSTALL_PREFIX/{bin,include/poppy,share/poppy/{css,img,js/dist}}
mkdir -p $HOME/.config/poppy

# copy files from source directory to install location
cp -f $MESON_SOURCE_ROOT/build/poppy $DESTDIR/$MESON_INSTALL_PREFIX/bin/poppy
cp -f $MESON_SOURCE_ROOT/include/globals.h $DESTDIR/$MESON_INSTALL_PREFIX/include/poppy/globals.h
cp -f $MESON_SOURCE_ROOT/protos/poppy.proto  $DESTDIR/$MESON_INSTALL_PREFIX/include/poppy/poppy.proto
cp -f $MESON_SOURCE_ROOT/share/poppy/envoy_poppy_proxy.yaml $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/envoy_poppy_proxy.yaml
cp -f $MESON_SOURCE_ROOT/share/poppy/index.html $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/index.html
cp -f $MESON_SOURCE_ROOT/poppy_sample.conf $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/poppy_sample.conf
cp -f $MESON_SOURCE_ROOT/LICENSE $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/LICENSE
cp -f $MESON_SOURCE_ROOT/README.md $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/README.md
cp -f $MESON_SOURCE_ROOT/share/poppy/css/index.css $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/css/index.css
cp -f $MESON_SOURCE_ROOT/share/poppy/img/poppy_logo.png $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/img/poppy_logo.png
cp -f $MESON_SOURCE_ROOT/share/poppy/js/package.json $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/js/package.json
cp -f $MESON_SOURCE_ROOT/share/poppy/js/package-lock.json $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/js/package-lock.json
cp -f $MESON_SOURCE_ROOT/share/poppy/js/dist/main.js $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/js/dist/main.js
cp -f $MESON_SOURCE_ROOT/share/poppy/js/dist/main.js.LICENSE.txt $DESTDIR/$MESON_INSTALL_PREFIX/share/poppy/js/dist/main.js.LICENSE.txt

if test -f "$HOME/.config/poppy/poppy.conf"; then
    echo "$HOME/.config/poppy/poppy.conf exists. Don't overwrite"
else
    cp -n $MESON_SOURCE_ROOT/poppy_sample.conf $HOME/.config/poppy/poppy.conf
fi
