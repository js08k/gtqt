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

#ifndef ___NAMESPACE___datapackage_h
#define ___NAMESPACE___datapackage_h

#include "export.h"
#include <message.h>

#include <QSharedData>
#include <QSharedDataPointer>

namespace __NAMESPACE__
{

/*!
 *  SharedPackageHelper is used as strictly a helper to shared package. This
 *  class allows for SharedPackage to create a class which inherits QSharedData
 *  without the class explicitly inheriting QSharedData.
 */
template <class T>
class DECL_EXPORT DataPackageHelper : public T, public QSharedData
{
public:
    // Expect T to have a default constructor
    DataPackageHelper() : T() { }

    // Expect T to have a default copy constructor
    DataPackageHelper( const T& other ) : T( other ) { }
};

/*!
 *  Shared QSharedDataPointer is inherited as private so that all functions
 *  could be hidden, to control the end users interaction with a Shared class.
 */
template <class T>
class DECL_EXPORT DataPackage
        : private QSharedDataPointer<DataPackageHelper<T> >
{
public:
    explicit DataPackage()
        : QSharedDataPointer<DataPackageHelper<T> >( new DataPackageHelper<T> )
    {

    }

    explicit DataPackage( DataPackageHelper<T>* sharedPackage )
        : QSharedDataPointer<DataPackageHelper<T> >( sharedPackage )
    {

    }

    explicit DataPackage( const DataPackageHelper<T>& other )
        : QSharedDataPointer<DataPackageHelper<T> >( other )
    {

    }

    explicit DataPackage( const T& other )
        : QSharedDataPointer<DataPackageHelper<T> >( new DataPackageHelper<T>( other ) )
    {

    }

    virtual ~DataPackage()
    {

    }

    const T* operator -> () const
    {
        return QSharedDataPointer<DataPackageHelper<T> >::constData();
    }

    const T& operator * () const
    {
        return *QSharedDataPointer<DataPackageHelper<T> >::constData();
    }

    T* data()
    {
        return QSharedDataPointer<DataPackageHelper<T> >::data();
    }

    const T* constData() const
    {
        return QSharedDataPointer<DataPackageHelper<T> >::constData();
    }
};
}

#endif // SHAREDPACKAGE_H

