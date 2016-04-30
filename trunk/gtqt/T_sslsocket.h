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


#ifndef ___NAMESPACE___sslsocket_h
#define ___NAMESPACE___sslsocket_h

// GtQt Includes
#include "socket.h"

// Qt Includes
#include <QSslSocket>

namespace __NAMESPACE__
{
class SslSocket : public QSslSocket, public __NAMESPACE__::Socket
{
    Q_OBJECT
public:
    // Constructor
    explicit SslSocket(QObject *parent = 0);

    // Destructor
    virtual ~SslSocket();

    /*!
     * \brief SslSocket::write
     * \param data
     */
    template <class T> void write( const T &message )
    {
        // QByteArray to contain the serialized message
        QByteArray serial;

        // Serialize the message
        // todo: Throw an exception if this fails?
        serialize( message, serial );

        // Transmit the message, count the data that has been sent.
        m_uploadCount += QSslSocket::write( serial.data(), serial.size() );
    }

private slots:
    // Slot called when data has arrived from a peer port
    void receiveSsl();
};
}

#endif // SSLSOCKET_H
