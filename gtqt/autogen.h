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


#ifndef AUTOGEN_H
#define AUTOGEN_H

#include <QMap>
#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QStringList>
#include <QPair>
#include <QDir>

class QString;
class QStringList;

class Autogen
{
public:
    enum RETURN_CODE
    {
        SUCCESS = 0,
        NO_IDL = 1,
        FAILED = 2
    };

    Autogen();


    void addIdlFileList( const QStringList& fileList );

    void addIdlFile( const QString& fileName );

    int generate();

private:
    static QString inputDir();
    static QString outputDir();
    static QString idlDir();

    void genRepeatCode( QByteArray &inputData );

    void findMessages();

    bool writeFile( const QString& fileName );

    static int32_t hash( const QString &data );

    // Verbose mode
    bool m_verbose;

    // The directory where the template files exists
    QDir const m_InputDir;

    // The directory to place the generated files
    QDir const m_OutputDir;

    // The directory containing the input idls (proto files)
    QDir m_IDLDir;

    // The list of files which need to be parsed
    QStringList m_fileList;

    // List of messages found
    QMap<QString,int32_t> m_messages;

    // Template for creating a switch statment
    QString m_switchCaseTemplate;

    /*** Autogen keywords with the data to replace them ***/
    QMap<QString, QString> m_Autocode;
};

#endif // AUTOGEN_H
