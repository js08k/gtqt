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
#include "sslsocket.h"

/*!
 * \brief SslSocket::SslSocket Constructor which connects the signal from
 * the Socket parent class. The signal is strictly a passthrough signal.
 * \param parent
 */
__NAMESPACE__::SslSocket::SslSocket(QObject *parent) :
    QSslSocket(parent)
{
    // Connect the socket's readyRead signal to receiveSsl
    connect( this, SIGNAL( readyRead() ), SLOT( receiveSsl() ) );
}

/*!
 * \brief SslSocket::~SslSocket
 */
__NAMESPACE__::SslSocket::~SslSocket()
{

}

/*!
 * \brief SslSocket::receiveSsl
 */
void __NAMESPACE__::SslSocket::receiveSsl()
{
    // Ensure at least the size of the header exists to be read
    while( bytesAvailable() >= 8 )
    {
        // Create a hear to inspect the incoming packet
        int32_t header[2];

        // Peek the header information from the packet
        peek( (char *)header, 8 );

        if( header[0] + 8 <= bytesAvailable() )
        {
            // Read in the message including the message's header
            QByteArray array = read( header[0] + 8 );

            // Pass the message to the parser
            receive( array );
        }
        else
        {
            qDebug() << "SSL Receiver: Discarding data, socket was it was in error.";
            readAll();
            break;
        }
    }
}
