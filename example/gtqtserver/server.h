/*
 * Copyright (c) , All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials
 * provided with the distribution. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <datapackage.h>

namespace gtqt { class UdpSocket; }
namespace gtqt { class TcpServer; }
namespace gtqt { class TcpSocket; }
namespace gtqt { class PeerLink; }

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
    ~Server();

signals:

public slots:

private slots:
    void receive( const gtqt::DataPackage<gtqt::ClientType1>& );
    void receive( const gtqt::DataPackage<gtqt::ClientType2>& );
    void newConnection();

private:
    bool const m_testTcp;
    bool const m_testUdp;
    gtqt::UdpSocket* m_udpServer;
    gtqt::TcpServer* m_tcpServer;
    gtqt::TcpSocket* m_tcpSocket;
    gtqt::PeerLink* m_link;
};

#endif // SERVER_H
