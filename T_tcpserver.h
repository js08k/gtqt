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


#ifndef __NAMESPACE__tcpserver_h
#define __NAMESPACE__tcpserver_h


#include "export.h"
// Qt Includes
#include <tcpsocket.h>

class QTcpServer;

namespace __NAMESPACE__ { class DECL_EXPORT TcpSocket; }
namespace __NAMESPACE__ { class DECL_EXPORT TcpServer; }

class DECL_EXPORT __NAMESPACE__::TcpServer
        : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer( QObject* parent = 0 );
    virtual ~TcpServer();
    void close();
    void listen( const QHostAddress&, quint16 );
    TcpSocket* nextPendingConnection();
    bool isListening() const;

signals:
    void newConnection();

private slots:
    void addDetails();

private:
    QTcpServer* m_tcpServer;
    QList<__NAMESPACE__::TcpSocket*> m_pending;
};

#endif
