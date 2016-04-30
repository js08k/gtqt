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


#include "server.h"

#include <udpsocket.h>
#include <tcpserver.h>
#include <tcpsocket.h>
//#include <receiver.h>
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
    , m_testTcp( true )
    , m_udpServer( NULL )
    , m_tcpServer( NULL )
    , m_tcpSocket( NULL )
{
    const QHostAddress addr( QHostAddress::LocalHost );
    const u_int16_t port( 6000 );

    if( m_testTcp )
    {
        m_tcpServer = new gtqt::TcpServer( this );
        connect( m_tcpServer, SIGNAL(newConnection()), SLOT(newConnection()) );
        m_tcpServer->listen( addr, port );
    }
    else
    {
        m_udpServer = new gtqt::UdpSocket( this );
        m_udpServer->bind( addr, port );

        connect( m_udpServer, SIGNAL(receive(gtqt::DataPackage<gtqt::ClientType1>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ClientType1>)) );
        connect( m_udpServer, SIGNAL(receive(gtqt::DataPackage<gtqt::ClientType2>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ClientType2>)) );
    }
}

Server::~Server()
{
    if( m_testTcp )
    {
        delete m_tcpServer;
    }
    else
    {
        delete m_udpServer;
    }
}

void Server::newConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();

    connect( m_tcpSocket, SIGNAL(receive(gtqt::DataPackage<gtqt::ClientType1>)),
             this, SLOT(receive(gtqt::DataPackage<gtqt::ClientType1>)) );
    connect( m_tcpSocket, SIGNAL(receive(gtqt::DataPackage<gtqt::ClientType2>)),
             this, SLOT(receive(gtqt::DataPackage<gtqt::ClientType2>)) );
}

void Server::receive(const gtqt::DataPackage<gtqt::ClientType1> &data )
{
    qDebug();
    qDebug() << "Received ClientType1:" << QString( data->data().c_str() );

    gtqt::DataPackage<gtqt::ServerType1> st1;
    st1.data()->set_data( data->data() + " from server" );

    if( m_testTcp )
    {
        if( m_tcpSocket )
        {
            m_tcpSocket->write( st1 );
        }
    }
    else
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 port( m_udpServer->peerPort( dest ) );
        m_udpServer->writeDatagram( st1, dest, port );
    }
}

void Server::receive(const gtqt::DataPackage<gtqt::ClientType2> &data )
{
    qDebug();
    qDebug() << "Received ClientType2:" << QString( data->data().c_str() );

    gtqt::DataPackage<gtqt::ServerType2> st2;
    st2.data()->set_data( data->data() + " from server" );

    if( m_testTcp )
    {
        if( m_tcpSocket )
        {
            m_tcpSocket->write( st2 );
        }
    }
    else
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 port( m_udpServer->peerPort( dest ) );
        m_udpServer->writeDatagram( st2, dest, port );
    }
}
