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

#ifndef ___NAMESPACE___peerlink_h
#define ___NAMESPACE___peerlink_h

// GtQt Includes
#include "export.h"
#include "datapackage.h"

// Qt Includes
#include <QMap>
#include <QObject>
#include <QHostAddress>

namespace __NAMESPACE__ { class PeerLink; }
namespace __NAMESPACE__ { class TcpSocket; }
namespace __NAMESPACE__ { class TcpServer; }

class DECL_EXPORT __NAMESPACE__::PeerLink
        : public QObject
{
    Q_OBJECT
public:
    explicit PeerLink( QObject* parent = 0 );
    virtual ~PeerLink();

    void close();
    void close( QHostAddress const&, quint16 );
    void listen( QHostAddress const&, quint16 );
    void connectToHost( QHostAddress const&, quint16 );
    void setAllowMulti( bool );

signals:
    void connected( QHostAddress const&, quint16 ) const;
    void disconnected( QHostAddress const&, quint16 ) const;
__REPEAT_START__
    void receive( __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> const& ) const;
__REPEAT_END__

public slots:
__REPEAT_START__
    void transmit( __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> const& );
__REPEAT_END__

private slots:
    void connected();
    void disconnected();
    void newConnection();

private:
    bool m_allowMulti;
    __NAMESPACE__::TcpServer* m_server;
    QMap<QString,__NAMESPACE__::TcpSocket*> m_peers;
};

#endif // PEERLINK_H
