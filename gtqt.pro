# To compile and use this code successfully version 2.6.0 over protoc must be
# used

TEMPLATE = subdirs

SUBDIRS	= \
    gtqt \
    example

example.depends = gtqt
example.subdir = example

OTHER_FILES += \
    README.md
