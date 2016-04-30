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


#ifndef ___NAMESPACE___tcpsocket_h
#define ___NAMESPACE___tcpsocket_h

// GtQt Includes
#include "socket.h"

// Qt Includes
#include <QTcpSocket>

class QHostAddress;

namespace __NAMESPACE__ { class TcpSocket; }

class __NAMESPACE__::TcpSocket
        : public QObject
        , public __NAMESPACE__::Socket
{
    Q_OBJECT
public:
    // Constructor
    explicit TcpSocket( QObject *parent = 0 );

    explicit TcpSocket( QTcpSocket* );

    // Destructor
    virtual ~TcpSocket();

    void connectToHost( const QHostAddress&, quint16, QIODevice::OpenMode mode = QIODevice::ReadWrite );

    /*!
     * \brief TcpSocket::write
     * \param data
     */
    template <class T> void write( const T &message );

signals:
__REPEAT_START__
    void receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void malformed() const;
    void connected() const;
    void disconnected() const;
    void error(QAbstractSocket::SocketError) const;

private slots:
    void receiveTcp();

private:
__REPEAT_START__
    void signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void signal_malformed() const;

    QTcpSocket* m_socket;
};

template <class T>
void __NAMESPACE__::TcpSocket::write( const T &message )
{
    // QByteArray to contain the serialized message
    QByteArray serial;

    // Serialize the message
    // todo: Throw an exception if this fails?
    serialize( message, serial );

    // Transmit the message, count the data that has been sent.
    m_uploadCount += m_socket->write( serial.data(), serial.size() );
}

#endif // TCPSOCKET_H