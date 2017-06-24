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


#include "client.h"

#include <udpsocket.h>
#include <tcpsocket.h>
#include <peerlink.h>
//#include <receiver.h>

#include <QDebug>
#include <QTimer>

Client::Client(QObject *parent)
    : QObject(parent)
    , m_testTcp( false )
    , m_testUdp( false )
    , m_udpClient( NULL )
    , m_tcpClient( NULL )
    , m_link( NULL )
{
    const QHostAddress addr( QHostAddress::LocalHost );
    const quint16 port( 6001 );

    if( m_testTcp )
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 destPort( 6000 );

        m_tcpClient = new gtqt::TcpSocket( this );
        m_tcpClient->connectToHost( dest, destPort );

        connect( m_tcpClient, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType1>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType1>)) );

        connect( m_tcpClient, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType2>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType2>)) );
    }
    else if ( m_testUdp )
    {
        m_udpClient = new gtqt::UdpSocket( this );
        m_udpClient->bind( addr, port );

        connect( m_udpClient, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType1>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType1>)) );

        connect( m_udpClient, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType2>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType2>)) );
    }
    else
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 destPort( 6000 );

        m_link = new gtqt::PeerLink(this);
        m_link->connectToHost( dest, destPort );
        connect( m_link, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType1>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType1>)) );
        connect( m_link, SIGNAL(receive(gtqt::DataPackage<gtqt::ServerType2>)),
                 this, SLOT(receive(gtqt::DataPackage<gtqt::ServerType2>)) );
    }

    QTimer* t = new QTimer( this );
    connect( t, SIGNAL(timeout()), this, SLOT(sendClientType1()) );
    connect( t, SIGNAL(timeout()), this, SLOT(sendClientType2()) );
    t->start( 5000 );
}

Client::~Client()
{
    delete m_udpClient;
}

void Client::sendClientType1()
{
    const QString string( "Client Type 1 test string" );

    qDebug();
    qDebug() << "Sending" << string;

    gtqt::DataPackage<gtqt::ClientType1> ct1;
    ct1.data()->set_data( qPrintable( string ) );

    if( m_testTcp )
    {
        m_tcpClient->write( ct1 );
    }
    else if ( m_testUdp )
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 port( 6000 );
        m_udpClient->writeDatagram( ct1, dest, port );
    }
    else
    {
        m_link->transmit(ct1);
    }
}

void Client::sendClientType2()
{
    const QString string( "Client Type 2 test string" );
    qDebug() << "Sending" << string;

    gtqt::DataPackage<gtqt::ClientType2> ct2;
    ct2.data()->set_data( qPrintable( string ) );

    if( m_testTcp )
    {
        m_tcpClient->write( ct2 );
    }
    else if ( m_testUdp )
    {
        const QHostAddress dest( QHostAddress::LocalHost );
        const quint16 port( 6000 );
        m_udpClient->writeDatagram( ct2, dest, port );
    }
    else
    {
        m_link->transmit(ct2);
    }
}

void Client::receive(const gtqt::DataPackage<gtqt::ServerType1> &data )
{
    qDebug() << "Received" << QString( data->data().c_str() );
}

void Client::receive(const gtqt::DataPackage<gtqt::ServerType2> &data )
{
    qDebug() << "Received" << QString( data->data().c_str() );
}
