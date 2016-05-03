QT       += core
QT       -= gui

TARGET = autogen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += \
    -lprotobuf

SOURCES += \
    main.cpp \
    autogen.cpp \

HEADERS += \
    autogen.h

# Google to Qt interface file templates
OTHER_FILES += \
    README \
    T_export.h \
    gtqtbuild.pri \
    T_gtqt.pro \
    protobf.pri \
    T_socket.h \
    T_socket.cpp \
    T_tcpsocket.cpp \
    T_tcpsocket.h \
    T_udpsocket.cpp \
    T_udpsocket.h \
    T_message.h \
    T_datapackage.h \
    T_sslsocket.cpp \
    T_sslsocket.h \
    T_tcpserver.cpp \
    T_tcpserver.h \
    T_file.cpp \
    T_file.h







