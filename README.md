# Brief
Genreates Tcp/Udp/SSL classes based around Qt network classes that transmit/receive messages (defined 
by the protoc IDL) as Qt signals and slots.

# Overview
This project takes the functionality of Protocol Buffers (https://developers.google.com/protocol-buffers/) and their
ability to serialize data writing and reading this data to Qt's provided socket functionality. The generated network 
classes emit Qt signals when message structures are received, and transmit these message structures when the messages
are passed to their slots. The overall result is a TcpSocket that behaves as a QTcpSocket however it now handles data
defined by the Protocol Buffer IDL rather than handling a QByteArray. QTcpServer, QTcpSocket, and QUdpSocket are all
currently supported.

# Currently tested systems
The written code was written strictly with the Qt library. This means that the code should not require any modification
in order to compile on Windows, Linux or Apple operating systems. So far, only the following linux distributions have
been tested: Ubuntu, Redhat

# Prerequisits
For the code to build, Qt libraries including qmake is required as well as the protoc binary from the Protocol Buffers
project. 
