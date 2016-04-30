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
#include "socket.h"

// Qt Includes
#include <QDebug>

// Std Includes
#include <string>

/*!
 * \brief Socket constructor. Initializes the data through put counters to zero
 * and registers the Shared message types for their use in Signals and Slots
 */
__NAMESPACE__::Socket::Socket()
{
    // Initialize the upload and download counters
    m_downloadCount = 0;
    m_uploadCount = 0;

__REPEAT_START__
        qRegisterMetaType<__NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> >( "__NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__>" );
__REPEAT_END__
}

/*!
 * \brief Socket deconstructor, place holder deconstructor
 */
__NAMESPACE__::Socket::~Socket()
{
    // Do nothing
}

/*!
 * \brief Receives and distributes a messsage to the proper parser (receiver
 * class) that was attached.
 * \param Buffer containing a single message and header
 */
void __NAMESPACE__::Socket::parse( const QByteArray &array )
{
    // Stop the receiver from reading messages that are obviously invalid
    // (All messages should have a header of 8 bytes)
    if( array.size() < 8 )
        return;

    // Create a pointer to the header. Message size will be the first entry and
    // message type will be the second entry.
    const int32_t* header = (const int32_t *)array.data();

    // Parse the header data creating two constants
    const int32_t messageSize = header[0];
    const int32_t messageType = header[1];

    // Input validation, to stop the server from any segmentation faults
    if( ( messageSize > 0 ) && ( messageSize + 8 <= array.size() ) )
    {
        // Create a QByteArray from the data following the header
        QByteArray buffer( array.data() + 8, messageSize );

        // Verify that data was created in the QByteArray
        if( buffer.size() > 0 )
        {
            // Increment the download count by the size of the
            // message and the header
            m_downloadCount += buffer.size() + 8;

            switch( messageType )
            {
__REPEAT_START__
                case Socket::__VALUE__:
                {
                    // Create a message to parse with
                    DataPackage<__NAMESPACE__::__KEY__> message;

                    // Attempt to parse the message
                    if( message.data()->ParseFromArray( buffer.data(), buffer.size() ) )
                    {
                        // Parse was successful, pass the message to the child
                        // for emiting as a signal
                        signal_receive( message );
                    }
                    else
                    {
                        // Inform the child class a malformed packet was
                        // received and discarded
                        signal_malformed();
                    }
                }
                    break;
__REPEAT_END__
            }
        }
    }
    else
    {
        // Inform the child class a malform packet was received and discarded.
        signal_malformed();
    }
}

__REPEAT_START__
/*!
 *  \brief __NAMESPACE__::Socket::serialize This function shall call the
 *  apropriate Google Protobuffer API in order to correctly serialize the
 *  __NAMESPACE__::__KEY__ message into the QByteArray refrence passed.
 *  \param message The message that is to be serialized.
 *  \param array This QByteArray is used to place the serialized message.
 *  \return True is returned if the serialize was successfull, otherwise false.
 *  \note: If false is returned the data in array is unmodified.
 */
bool __NAMESPACE__::Socket::serialize( const __NAMESPACE__::__KEY__& message, QByteArray &array ) const
{
    // std string to hold the serialized value
    std::string serialized;

    // Serialze the value, and check the return value
    if( message.SerializeToString( &serialized ) )
    {
        // Clear out any data that may be in the QByteArray.
        array.clear();

        // Create the header: message size as first entry, type as second
        int32_t header[2] = { int32_t( serialized.length() ), Socket::__VALUE__ };

        // Write the 8 byte header for the message
        array.append( (const char *)header, 8 );

        // Write the message, recording the number of bytes written
        array.append( serialized.data(), serialized.size() );

        // Operation was successfull, returning true
        return true;
    }
    else
    {
        // Unable to serialize the message, returning false.
        return false;
    }
}

/*!
 *  \brief __NAMESPACE__::Socket::serialize This function is a convenience
 *  interface to the other serialize function. This will simply pull the
 *  data from the Shared pointer and call the serialize which does not handled
 *  shared pointers.
 *  \param message The shared message that is to be serialized.
 *  \param array This QByteArray is used to place the serialized message.
 *  \return True is returned if the serialize was successfull, otherwise false.
 *  \note: If false is returned the data in array is unmodified.
 */
bool __NAMESPACE__::Socket::serialize( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__>& message, QByteArray &array ) const
{
    return serialize( *message, array );
}
__REPEAT_END__

