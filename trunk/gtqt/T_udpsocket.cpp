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
#include "udpsocket.h"

/*!
 * \brief UdpSocket::UdpSocket Constructor connects the signal from
 * the QUdpSocket parent class.
 * \param parent Pointer to the parent of the UdpSocket.
 */
__NAMESPACE__::UdpSocket::UdpSocket( QObject *parent )
    : QObject( parent )
    , m_socket( NULL )
{
    // Create a new QUdpSocket
    m_socket = new QUdpSocket( this );

    // Connect the socket's readyRead signal to receiveUdp slot
    connect( m_socket, SIGNAL( readyRead() ), SLOT( receiveUdp() ) );
}

/*!
 * \brief __NAMESPACE__::UdpSocket::UdpSocket Constructor to create a UdpSocket
 * from a already existing QUdpSocket.
 * \param udpSocket Already created QUdpSocket
 */
__NAMESPACE__::UdpSocket::UdpSocket( QUdpSocket* socket  )
    : QObject( socket )
    , m_socket( socket )
{
    // Connect the socket's readyRead signal to receiveUdp slot
    connect( m_socket, SIGNAL( readyRead() ), SLOT( receiveUdp() ) );
}

/*!
 * \brief UdpSocket::~UdpSocket Destructor
 */
__NAMESPACE__::UdpSocket::~UdpSocket()
{

}

/*!
 * \brief UdpSocket::receiveUdp Slot called when the QUdpSocket
 * receives data from the network. This will utamatly emit a signal
 * with the message parsed.
 */
void __NAMESPACE__::UdpSocket::receiveUdp()
{
    // Byte array for receiving each datagram
    QByteArray datagram;

    // Peer address, will be populated when receiving the datagram
    QHostAddress host;

    // Peer port, will be populated when receiving the datagram
    quint16 port;

    // Continue in this loop while data is there to be read
    while( m_socket->hasPendingDatagrams() )
    {
        // Byte array to receive the datagram
        datagram.resize( m_socket->pendingDatagramSize() );

        // Read in the datagram from the QUdpSocket API
        m_socket->readDatagram( datagram.data(), datagram.size(), &host, &port );

        {
            // Scoping the lock duration
            // Lock the UdpSocket instance
            QMutexLocker lock( &m_serverLock );
            Q_UNUSED( lock )

            // Insert the port lookup
            m_peerLookup.insert( host, port );
        }

        // Pass the message to the parser
        parse( datagram );
    }
}

/*!
 * \brief UdpSocket::bind
 * \param address
 * \param port
 * \return
 */
bool __NAMESPACE__::UdpSocket::bind( const QHostAddress &address, quint16 port )
{
    QMutexLocker lock( &m_serverLock );
    Q_UNUSED( lock );

    // Call the QUdpSocket::bind
    return m_socket->bind( address, port );
}

/*!
 * \brief UdpSocket::peerPort
 * \param host
 * \return
 */
quint16 __NAMESPACE__::UdpSocket::peerPort( const QHostAddress& host )
{
    QMutexLocker lock( &m_serverLock );
    Q_UNUSED( lock );

    // Look for the Address in the table
    if( m_peerLookup.contains( host ) )
    {
        // Address was found, return the peer port cooresponding
        return m_peerLookup[ host ];
    }
    else
    {
        // Return zero as the port, indicating that it was not found
        return 0;
    }
}

__REPEAT_START__
void __NAMESPACE__::UdpSocket::signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> data ) const
{
    emit receive( data );
}
__REPEAT_END__

void __NAMESPACE__::UdpSocket::signal_malformed() const
{
    emit malformed();
}
