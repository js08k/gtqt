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

#include "autogen.h"

// Qt Includes
#include <QStringListIterator>
#include <QCoreApplication>
#include <QStringList>
#include <QRegExp>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

// C++ Includes
#include <iostream>

int main( int argc, char *argv[] )
{
    QCoreApplication a( argc, argv );

    Q_UNUSED( a )

    QStringList arguments = QCoreApplication::arguments();

    // Search for the Input directory flags
    int index = arguments.indexOf(
                QRegExp( "^-?h(elp)?$", Qt::CaseInsensitive ) );

    if( index > -1 || ( QCoreApplication::arguments().size() < 2 ) )
    {
        std::cout << "Usage: " << qPrintable( arguments.at( 0 ) );
        std::cout << " [ options ] idl_1 [ idl_2 ... ]\n" << std::endl;
        std::cout << "options: [default]\n";
        std::cout << "  indir=[.]           Directory containing the template files.\n";
        std::cout << "  outdir=[.]          Directory to place generated files.\n";
        std::cout << "  idldir=[.]          Directory containing the idl/proto files.\n";
        std::cout << "  namespace=[gtqt]    Namespace to be used within generated files.\n";
        return 1;
    }

    // Create the code generator
    Autogen generator;

    generator.generate();

    return 0;

    //return generator.generate();
}
