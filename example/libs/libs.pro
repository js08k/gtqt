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

IDL_DIR = $${_PRO_FILE_PWD_}

# Directory of the GTQT templates
GTQT_SRC = $${_PRO_FILE_PWD_}/../../gtqt

# Directory containing compiled gtqt
GTQT_DIR = $${OUT_PWD}/../../gtqt

# Destination of the autogenrated library
GTQT_DESTDIR = $${OUT_PWD}

# Google protocol buffer IDL files
PROTOS = \
    example1.proto \
    example2.proto

OTHER_FILES += \
    $${PROTOS}

include( ../../gtqt/gtqtbuild.pri )

QT -= gui

TEMPLATE = lib
