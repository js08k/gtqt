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
#include "tcpsocket.h"

/*!
 * \brief TcpSocket::TcpSocket Constructor which connects the signal from
 * the Socket parent class. The signal is strictly a passthrough signal.
 * \param parent
 */
__NAMESPACE__::TcpSocket::TcpSocket(QObject *parent)
    : QObject( parent )
    , m_socket( NULL )
{
    // Generate a new QTcpSocket with this as the parent
    m_socket = new QTcpSocket( this );

    // Connect the socket's readyRead signal to receiveTcp
    connect( m_socket, SIGNAL(readyRead()), SLOT(receiveTcp()) );
    connect( m_socket, SIGNAL(connected()), SIGNAL(connected()) );
    connect( m_socket, SIGNAL(disconnected()), SIGNAL(disconnected()) );
    connect( m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
             SIGNAL(error(QAbstractSocket::SocketError)) );
}

__NAMESPACE__::TcpSocket::TcpSocket( QTcpSocket* socket )
    : QObject( socket )
    , m_socket( socket )
{
    // Connect the socket's readyRead signal to receiveTcp
    connect( m_socket, SIGNAL(readyRead()), SLOT( receiveTcp() ) );
    connect( m_socket, SIGNAL(connected()), SIGNAL(connected()) );
    connect( m_socket, SIGNAL(disconnected()), SIGNAL(disconnected()) );
    connect( m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
             SIGNAL(error(QAbstractSocket::SocketError)) );
}

/*!
 * \brief TcpSocket::~TcpSocket
 */
__NAMESPACE__::TcpSocket::~TcpSocket()
{
    m_socket->deleteLater();
    m_socket = 0;
}

void __NAMESPACE__::TcpSocket::connectToHost( const QHostAddress& addr, quint16 port, QIODevice::OpenMode mode )
{
    m_socket->connectToHost( addr, port, mode );
}

/*!
 * \brief TcpSocket::receiveTcp
 */
void __NAMESPACE__::TcpSocket::receiveTcp()
{
    // Ensure at least the size of the header exists to be read
    while( m_socket->bytesAvailable() >= 8 )
    {
        // Create a hear to inspect the incoming packet
        int32_t header[2];

        // Peek the header information from the packet
        m_socket->peek( (char *)header, 8 );

        if( header[0] + 8 <= m_socket->bytesAvailable() )
        {
            // Read in the message including the message's header
            QByteArray array = m_socket->read( header[0] + 8 );

            // Pass the message to the parser
            parse( array );
        }
        else
        {
            m_socket->readAll();
            break;
        }
    }
}

__REPEAT_START__
void __NAMESPACE__::TcpSocket::signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> data ) const
{
    emit receive( data );
}
__REPEAT_END__

void __NAMESPACE__::TcpSocket::signal_malformed() const
{
    emit malformed();
}
