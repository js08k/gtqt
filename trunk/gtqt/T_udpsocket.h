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


#ifndef ___NAMESPACE___udpsocket_h
#define ___NAMESPACE___udpsocket_h

// GtQt Includes
#include "socket.h"

// Qt Includes
#include <QUdpSocket>
#include <QMutexLocker>

class QHostAddress;

namespace __NAMESPACE__ { class UdpSocket; }

class __NAMESPACE__::UdpSocket
        : public QObject
        , public __NAMESPACE__::Socket
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = 0);
    explicit UdpSocket( QUdpSocket* );
    virtual ~UdpSocket();

    /*!
     * \brief UdpSocket::writeDatagram
     * \param datagram
     * \param host
     * \param port
     */
    template <class T>
    void writeDatagram( DataPackage<T> const&, QHostAddress const&, quint16 );

    /*!
     *
     *
     */
    // Udp specific for binding to the host
    bool bind( const QHostAddress &address, quint16 port );

    // Get a peer source port given an address
    quint16 peerPort( const QHostAddress & );

signals:
__REPEAT_START__
    void receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void malformed() const;

private slots:
    void receiveUdp();

private:
__REPEAT_START__
    void signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void signal_malformed() const;

    // Allow to do operations from multiple threads
    QMutex m_serverLock;

    // Create a port lookup for peers based on address
    QHash<QHostAddress,quint16> m_peerLookup;

    QUdpSocket* m_socket;
};


template <class T>
void __NAMESPACE__::UdpSocket::writeDatagram(
        DataPackage<T> const& message, QHostAddress const& host, quint16 port )
{
    QMutexLocker locker( &m_serverLock );
    Q_UNUSED( locker )

    QByteArray serial;

    serialize( message, serial );

    m_uploadCount += m_socket->writeDatagram( serial, host, port );
}

#endif // UDPSOCKET_H
