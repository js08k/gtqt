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


#ifndef ___NAMESPACE___message_h
#define ___NAMESPACE___message_h

#include "export.h"

// Includes that the autogenerator will need to add
__PROTO_INCLUDES__

namespace __NAMESPACE__ { template <typename T> class DECL_EXPORT Traits; }
__REPEAT_START__
namespace __NAMESPACE__ { class DECL_EXPORT __KEY__; }
__REPEAT_END__

template <typename T> class DECL_EXPORT __NAMESPACE__::Traits
{
public:

    /*!
         * \brief GoogleType This type should be set from T to the proper
         * type in a partial template specification.
         */
    typedef T GoogleType;

    /*!
         * \brief QtType This type should be set from T to the proper type
         * in a partial template specification.
         */
    typedef T QtType;

    // Default KeyCount is zero
    //        enum { KeyCount = 0 };

    // Single KeyType is defined as K
    //        typedef T K;

    // Single KeyType conversion functions
    //        const K& key( const T& );

    /*!
         * \brief googleToQt Converts data from a google type into a Qt Type.
         * This should have a partial template implementation for each message
         * type that will need to make use of these functions.
         * \param GoogleType const refrence of the google typed data.
         * \param QtType mutable refrence to the qt typed data destination.
         * \return True on a successful conversion, otherwise False.
         */
    bool toQtType( const GoogleType& googletype, QtType& qttype ) const;

    /*!
         * \brief googleFromQt Converts data from a Qt type into a google type.
         * This should have a partial template implementation for each message
         * type that will need to make use of these functions.
         * \param googletype mutable refrence to the destination of the data
         * \param qttype a const refrence to the source of the data.
         * \return True on a successful conversion, otherwise False.
         */
    bool fromQtType( GoogleType& googletype, const QtType& qttype ) const;

    //        bool operator == ( const T& ) const;

    //        bool operator < ( const T& ) const;

};

__REPEAT_START__
class DECL_EXPORT __NAMESPACE__::__KEY__
        : public __PACKAGE__::__KEY__
{
public:
    /*!
        * \brief __KEY__ default constructor
        */
    __KEY__()
    {
        // Intentionally doing nothing here
    }

    __KEY__( const __PACKAGE__::__KEY__& orig )
        : __PACKAGE__::__KEY__( orig )
    {

    }

    /*!
        * \brief __KEY__ default deconstructor
        */
    virtual ~__KEY__()
    {
        // Intentionally doing nothing here
    }
};
__REPEAT_END__

#endif // MESSAGE_H
