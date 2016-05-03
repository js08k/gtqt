# todo: Add the google protocol buffers svn co as a subdirectory
# and a qmake script that will autobuild the checked out code correctly

# To compile this code, the following packages are required. It does not
# explicitly require version 8, however each package must be from the same
# version.
#
# 1) protobuf-compiler
# -- 2) libprotoc8
# -- 3) libprotoc-dev
# -- 4) libprotobuf8
# -- 5) libprotobuf-lite8
# -- 6) libprotobuf-dev

TEMPLATE = subdirs

SUBDIRS	= \
    gtqt \
    example

example.depends = gtqt
example.subdir = example

OTHER_FILES += \
    README.md
