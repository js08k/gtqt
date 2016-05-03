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

# Note: This file does not need to be modified in order to function
# only included in the .pro

# todo: Use qmake's external compilers to perform all the work
# done in this file.

isEmpty(PROTOS) {
    error( PROTOS variable must be defined before including gtqtbuild.pri )
}

isEmpty(IDL_DIR) {
    error( IDL_DIR variable must be defined before including gtqtbuild.pri )
}

isEmpty(GTQT_DIR) {
    error( GTQT_DIR variable must be defined before including gtqtbuild.pri )
}

isEmpty(GTQT_SRC) {
    error( GTQT_SRC variable must be defined before including gtqtbuild.pri )
}

isEmpty(GTQT_DESTDIR) {
    error( GTQT_DESTDIR variable must be defined before including the gtqtbuild.pri)
}

for(p, PROTOS):IDLS += $${_PRO_FILE_PWD_}/$${p}
for(p, PROTOS):IDLS_OUT += $${GTQT_DESTDIR}/$${p}

# Create the output directory if it does not already exists
gtqt_outdir.commands = mkdir -p $${GTQT_DESTDIR}

# Copy the protobf.pri file to the gtqt's output directory
gtqt_setup.target = $${GTQT_DESTDIR}/protobf.pri
gtqt_setup.commands = cp $${GTQT_SRC}/protobf.pri $${GTQT_DESTDIR}

QMAKE_CLEAN += $${GTQT_DESTDIR}/protobf.pri
QMAKE_DISTCLEAN += $${GTQT_DESTDIR}/protobf.pri

# Generate the gtqt source files from the templates & specified idl files
gtqt_generate.target = $${GTQT_DESTDIR}/gtqt.pro
gtqt_generate.commands = $${GTQT_DIR}/autogen indir=$${GTQT_SRC} \
    outdir=$${GTQT_DESTDIR} idldir=$${IDL_DIR} $${PROTOS}
gtqt_generate.depends = gtqt_setup $${IDLS} $${GTQT_SRC}/T_* $${GTQT_DIR}/autogen

QMAKE_CLEAN += $${GTQT_DESTDIR}/*.cpp $${GTQT_DESTDIR}/*.h $${GTQT_DESTDIR}/*.cc
QMAKE_DISTCLEAN += $${GTQT_DESTDIR}/*.cpp $${GTQT_DESTDIR}/*.h $${GTQT_DESTDIR}/*.cc

# Run qmake in gtqt's output directory
gtqt_configure.target = $${GTQT_DESTDIR}/gtqt.Make
gtqt_configure.commands = qmake CONFIG+=$${GTQT_CONFIG} $${GTQT_DESTDIR} -o $${GTQT_DESTDIR}/gtqt.Make
gtqt_configure.depends = $${gtqt_generate.target}

QMAKE_CLEAN += $${GTQT_DESTDIR}/*.pro
QMAKE_DISTCLEAN += $${GTQT_DESTDIR}/*.pro $${GTQT_DESTDIR}/gtqt.Make

# Build the gtqt
gtqt_build.commands = make -C $${GTQT_DESTDIR} -f gtqt.Make
gtqt_build.depends = gtqt_configure

QMAKE_CLEAN += $${GTQT_DESTDIR}/*.o
QMAKE_DISTCLEAN += $${GTQT_DESTDIR}/libgtqt.so*

QMAKE_EXTRA_TARGETS += \
    gtqt_outdir \
    gtqt_setup \
    gtqt_generate \
    gtqt_configure \
    gtqt_build

PRE_TARGETDEPS += \
    gtqt_outdir \
    gtqt_build
