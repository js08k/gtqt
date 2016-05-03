#
#  Copyright (c) , All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer. Redistributions in binary
#  form must reproduce the above copyright notice, this list of conditions and
#  the following disclaimer in the documentation and/or other materials
#  provided with the distribution. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
#  HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
#  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Google protocol buffer IDL files
PROTOS = \
    __PROTO_FILES__

# Google Protocol buffer build files
include( protobf.pri )

QT       -= gui
QT       += network

TARGET = __NAMESPACE__

TEMPLATE = lib

DEFINES += COMMS_LIBRARY

if(contains(CONFIG,staticlib)) {
message( Compiling static )
    DEFINES -= DLL_EXPORT
} else {
message( Compiling dynamic )
    DEFINES += DLL_EXPORT
}

SOURCES += \
    socket.cpp  \
    udpsocket.cpp \
    tcpsocket.cpp \
    tcpserver.cpp \
    file.cpp \
#    sslsocket.cpp

HEADERS += \
    export.h \
    message.h \
    datapackage.h \
    socket.h \
    tcpsocket.h \
    udpsocket.h \
    tcpserver.h \
    file.h \
#    sslsocket.h

