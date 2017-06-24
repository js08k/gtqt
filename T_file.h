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


#ifndef ___NAMESPACE___file_h
#define ___NAMESPACE___file_h

#include "export.h"
#include "socket.h"

#include <QFile>

namespace __NAMESPACE__ { class DECL_EXPORT File; }

class DECL_EXPORT __NAMESPACE__::File
        : public QObject
        , public __NAMESPACE__::Socket
{
    Q_OBJECT
public:
    explicit File( QObject *parent = 0 );
    explicit File( QFile* );
    virtual ~File();

    template <class T> void write( const T& message )
    {
        QByteArray serial;
        serialize( message, serial );
        m_file->write( serial.data(), serial.size() );
    }

    void read();

signals:
__REPEAT_START__
    void read( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void malformed() const;

private:
__REPEAT_START__
    void signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const;
__REPEAT_END__

    void signal_malformed() const;

    QFile* m_file;
};

#endif // ___NAMESPACE___file_h
