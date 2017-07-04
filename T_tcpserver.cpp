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


// GtQt Includes
#include "tcpserver.h"

#include "tcpsocket.h"

#include <QTcpServer>

__NAMESPACE__::TcpServer::TcpServer(QObject* parent)
    : QObject( parent )
    , m_tcpServer( NULL )
{
    m_tcpServer = new QTcpServer( this );

    connect( m_tcpServer, SIGNAL( newConnection() ),
             this, SLOT( addDetails() ) );
}

__NAMESPACE__::TcpServer::~TcpServer()
{

}

void __NAMESPACE__::TcpServer::close()
{
    m_tcpServer->close();
}

void __NAMESPACE__::TcpServer::listen( const QHostAddress& addr, quint16 port )
{
    m_tcpServer->listen( addr, port );
}

void __NAMESPACE__::TcpServer::addDetails()
{
    QTcpSocket* qsocket = m_tcpServer->nextPendingConnection();

    if( qsocket )
    {
        TcpSocket* socket = new TcpSocket( qsocket );
        m_pending.append( socket );
        emit newConnection();
    }
}

__NAMESPACE__::TcpSocket* __NAMESPACE__::TcpServer::nextPendingConnection()
{
    if( m_pending.isEmpty() )
    {
        return NULL;
    }
    else
    {
        return m_pending.takeFirst();
    }
}

bool __NAMESPACE__::TcpServer::isListening() const
{
    return m_tcpServer->isListening();
}

