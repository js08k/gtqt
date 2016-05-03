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


#ifndef ___NAMESPACE___socket_h
#define ___NAMESPACE___socket_h

#include "export.h"
#include "datapackage.h"
//#include "receiver.h"

namespace __NAMESPACE__
{
class DECL_EXPORT Socket
{
private:

    //! Provides a Enumeration between a message type and a unique integer
    enum MessageType
    {
        __MESSAGE_ENUMS__
    };

public:
    explicit Socket();

    virtual ~Socket();

protected:
__REPEAT_START__
    //! \brief Takes in a protobuffer type and encodes into a QByteArray
    bool serialize( const __KEY__&, QByteArray & ) const;

    //! \brief Convience function to take in a Shared Message Pointer and
    //! encode into a QByteArray
    bool serialize( const DataPackage<__KEY__>&, QByteArray & ) const;

    // Implemented by the child class, provides a interface to indicate when
    // a parsed message has been validated.
    virtual void signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> ) const = 0;
__REPEAT_END__

    //! \brief Callback to the child class to indicate the reception of a
    //! malformed packet
    virtual void signal_malformed() const = 0;

    //! \brief Parses a message from the wire, determining which message type
    //! was received, eventually making a call to the callback with the
    //! resulting message.
    void parse( const QByteArray& );

    //! Counter to track the amount of data received by this socket
    int m_downloadCount;

    //! Counter to track the amount of data transmitted by this socket
    int m_uploadCount;
};
}

#endif // ___NAMESPACE___socket_h
