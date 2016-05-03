/*
 * BSD 2-Clause License (FreeBSD/Simplified)
 *
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
#include <QString>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QStringListIterator>
#include <QMapIterator>
#include <QCoreApplication>
#include <QDir>
#include <iostream>

// Google's Protocol Compiler Includes
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

/*!
 * \brief Autogen::Autogen
 * \param inputdir
 * \param outputdir
 */
Autogen::Autogen()
    : m_verbose( false )
    , m_InputDir( inputDir() )
    , m_OutputDir( outputDir() )
    , m_IDLDir( idlDir() )
{
    // Add the scopename to the list of string replace keys
    m_Autocode.insert( "__NAMESPACE__", scopeName() );

    // Get a copy of the application arguments
    QStringList args( QCoreApplication::arguments() );

    // Remove the program name from the arguments
    args.takeFirst();

    // Remove indir, outdir and idldir arguments
    args = args.filter( QRegExp("^(?!indir=\\S*)",Qt::CaseInsensitive) );
    args = args.filter( QRegExp("^(?!outdir=\\S*)",Qt::CaseInsensitive) );
    args = args.filter( QRegExp("^(?!idldir=\\S*)",Qt::CaseInsensitive) );
    args = args.filter( QRegExp("^(?!namespace=\\S*)",Qt::CaseInsensitive) );

    // Assume all resulting arguments are idl files
    addIdlFileList( args );
}

QString Autogen::inputDir()
{
    QStringList const args( QCoreApplication::arguments() );
    int const index( args.indexOf(QRegExp("indir=\\S*", Qt::CaseInsensitive)) );

    if ( index == -1 )
    {
        return QCoreApplication::applicationDirPath();
    }
    else
    {
        // Remove the indir argument from the argument list
        QString temp( args.at(index) );

        // Remove the "indir=" string from the argument
        temp.remove( QRegExp("indir=", Qt::CaseInsensitive) );

        if ( !QDir(temp).exists() )
        {
            // Assume it is a relative path
            QString relative( QCoreApplication::applicationDirPath()+"/"+temp );

            // Check the directory exists
            if ( !QDir(relative).exists() )
            {
                // Give up looking for the directory
                std::cerr << "Specified input directory was not found: "
                          << temp.toStdString() << std::endl;

                // Close the application with an error
                exit(1);
            }

            // Return the relative path to be used
            return relative;
        }

        // Return the full path to be used
        return temp;
    }
}

QString Autogen::outputDir()
{
    QStringList const args( QCoreApplication::arguments() );
    int const index( args.indexOf(QRegExp("outdir=\\S*", Qt::CaseInsensitive)) );

    if ( index == -1 )
    {
        return QCoreApplication::applicationDirPath();
    }
    else
    {
        // Remove the indir argument from the argument list
        QString temp( args.at(index) );

        // Remove the "indir=" string from the argument
        temp.remove( QRegExp("outdir=", Qt::CaseInsensitive) );

        if ( !QDir(temp).exists() )
        {
            // Assume it is a relative path
            QString relative( QCoreApplication::applicationDirPath()+"/"+temp );

            // Check the directory exists
            if ( !QDir(relative).exists() )
            {
                // Give up looking for the directory
                std::cerr << "Specified output directory was not found: "
                          << temp.toStdString() << std::endl;

                // Close the application with an error
                exit(1);
            }

            // Return the relative path to be used
            return relative;
        }

        // Return the full path to be used
        return temp;
    }
}

QString Autogen::idlDir()
{
    QStringList const args( QCoreApplication::arguments() );
    int const index( args.indexOf(QRegExp("idldir=\\S*", Qt::CaseInsensitive)) );

    if ( index == -1 )
    {
        return QCoreApplication::applicationDirPath();
    }
    else
    {
        // Remove the indir argument from the argument list
        QString temp( args.at(index) );

        // Remove the "indir=" string from the argument
        temp.remove( QRegExp("idldir=", Qt::CaseInsensitive) );

        if ( !QDir(temp).exists() )
        {
            // Assume it is a relative path
            QString relative( QCoreApplication::applicationDirPath()+"/"+temp );

            // Check the directory exists
            if ( !QDir(relative).exists() )
            {
                // Give up looking for the directory
                std::cerr << "Specified idldir was not found: "
                          << temp.toStdString() << std::endl;

                // Close the application with an error
                exit(1);
            }

            // Return the relative path to be used
            return relative;
        }

        // Return the full path to be used
        return temp;
    }
}

QString Autogen::scopeName()
{
    QStringList const args( QCoreApplication::arguments() );
    int const index( args.indexOf(QRegExp("namespace=\\S*", Qt::CaseInsensitive)) );

    if ( index == -1 )
    {
        return QString("gtqt");
    }
    else
    {
        QString scopename( args.at(index) );
        scopename.remove( QRegExp("namespace=",Qt::CaseInsensitive) );

        // TODO Some error checking to make sure the namespace is acceptable
        return scopename;
    }
}

/*!
 * \brief Autogen::addIdlFileList
 * \param fileList
 */
void Autogen::addIdlFileList( const QStringList& fileList )
{
    QStringListIterator iterator( fileList );

    while( iterator.hasNext() )
    {
        addIdlFile( iterator.next() );
    }
}

/*!
 * \brief Autogen::addIdlFile
 * \param fileName
 */
void Autogen::addIdlFile( const QString& fileName )
{
    if( !m_fileList.contains( fileName ) )
    {
        // Create a QFileInfo object to help in chopping off any relative path
        // non-sense that will muck up how to get to the file.
        QFileInfo choprelative( fileName );

        // Chop off any relative file stuff and set the file relative to the
        // passed IDL directory. fileName() method will return the file's name
        // only without relative path information.
        QFileInfo file( m_IDLDir, choprelative.fileName() );

        if( !file.exists() )
        {
            std::cerr << "Unable to find file: "
                      << qPrintable( file.filePath() )
                      << std::endl;
            exit( -1 );
        }
        else
        {
            if( file.suffix() == QString( "proto" ) )
            {
                // Insert the IDL file into the input file list
                m_fileList.append( file.filePath() );

                QString &protofiles =
                        m_Autocode[ QString( "__PROTO_FILES__" ) ];

                protofiles.append( file.filePath() );
                protofiles.append( " \\ \n" );

                QString &protoinclude =
                        m_Autocode[ QString( "__PROTO_INCLUDES__" ) ];

                protoinclude.append( "#include \"" );
                protoinclude.append( file.completeBaseName() );
                protoinclude.append( ".pb.h\"\n" );
            }
            else
            {
                std::cerr << "Only able to handle *.proto file endings."
                          << std::endl;
                exit( -1 );
            }
        }
    }
}

class MockErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector
{
public:
    MockErrorCollector()
    {
        errors = 0;
    }
    ~MockErrorCollector() {}

    int errors;

    // implements ErrorCollector ---------------------------------------
    void AddError(const std::string& filename, int line, int column,
                  const std::string& message)
    {
        QString string( QString( filename.c_str() ) + ":" +
                        QString::number( line ) + ":" +
                        QString::number( column ) + ": " +
                        QString( message.c_str() ) );
        std::cerr << qPrintable( string ) << std::endl;
        ++errors;
    }
};


/*!
 * \brief Autogen::newFindMessages to replace findMessages
 */
void Autogen::findMessages()
{
    using namespace google::protobuf;
    using namespace google::protobuf::compiler;

    MockErrorCollector collector;
    compiler::DiskSourceTree source_tree;
    source_tree.MapPath( "", qPrintable( m_IDLDir.path() ) );
    compiler::Importer import( &source_tree, &collector );

    QStringListIterator filesIterator( m_fileList );

    while( filesIterator.hasNext() )
    {
        // Get the file (these are saved as full path)
        QString filename( filesIterator.next() );

        // Create a file name relative to the IDL directory
        filename = QDir( m_IDLDir ).relativeFilePath( filename );

        const FileDescriptor* fd = import.Import( qPrintable( filename ) );

        if( fd )
        {
            for( int i = 0; i < fd->message_type_count(); ++i )
            {
                const Descriptor* d = fd->message_type( i );

                if( d )
                {
                    QString message( d->name().c_str() );

                    if( m_messages.contains( message ) )
                    {
                        std::cerr << "Error: " << qPrintable( message )
                                  << " was found twice." << std::endl;
                        exit( -1 );
                    }
                    else
                    {
                        m_messages.insert( message, hash( message ) );
                    }
                }
            }

            QString package( fd->package().c_str() );
            m_Autocode.insert( "__PACKAGE__", package );
        }
    }

    if( collector.errors > 0 )
    {
        exit( -1 );
    }

    QMapIterator<QString,int32_t> messagesIterator( m_messages );

    while( messagesIterator.hasNext() )
    {
        messagesIterator.next();

        // Get a refrence to the string that will replace "__MESSAGE_ENUMS__" key
        QString &autocode = m_Autocode[ "__MESSAGE_ENUMS__" ];

        // Append the enumeration with it's assigned value
        autocode.append( messagesIterator.key().toUpper() );
        autocode.append( " = " );
        autocode.append( QString::number( messagesIterator.value() ) );


        if( messagesIterator.hasNext() )
        {
            autocode.append( ",\n" );
        }
        else
        {
            autocode.append( "\n" );
        }
    }
}

/*!
 * \brief Autogen::generate
 */
int Autogen::generate()
{
    if( m_fileList.size() < 1 )
    {
        std::cerr << "At least one idl file must be specified." << std::endl;
        return NO_IDL;
    }

    // Pull out message keywords from the input files
    findMessages();

    // Create a directory object using the input file.
    QDir inputDir( m_InputDir );

    // Get a list of all files in the input directory
    QStringList files = inputDir.entryList( QDir::Files );

    // Create an iterator to look at each file in the input directory
    QStringListIterator iterator( files );

    // Iterate through the files...
    while( iterator.hasNext() )
    {
        QString fileName = iterator.next();

        if( fileName.contains( QRegExp( "^T_\\S*\\.(h|cpp|cc|c|pro)$" ) ) )
        {
            // If the template file is found in the directory,
            // generate an output file for the template file
            if( writeFile( fileName ) == false )
            {
                return FAILED;
            }
        }
    }

    return SUCCESS;
}

/*!
 * \brief Autogen::writeFile
 * \param fileName
 */
bool Autogen::writeFile(const QString &fileName)
{
    // Set the template as the input
    QFile input( m_InputDir.path() + "/" + fileName );

    // Remove the template keyword from the file name and set as output
    QFile output( m_OutputDir.path() + "/" + QString( fileName ).remove( QRegExp( "T_" ) ) );

    // Open the input file as readonly
    if( !input.open( QFile::ReadOnly ) )
    {
        // Unable to read the file, this is a fatal error.
        std::cerr << "Unable to read " << qPrintable( input.fileName() )
                  << std::endl;
        return false;
    }

    // Open the output file as writeonly
    if( !output.open( QFile::WriteOnly ) )
    {
        // Unable to write the file, this is a fatal error
        std::cerr << "Unable to write " << qPrintable( output.fileName() )
                  << std::endl;
        return false;
    }

    // Attempt to read all the file into a single QByteArray
    QByteArray inputData = input.readAll();

    if( !inputData.isNull() )
    {
        // Generate the repeate code, inputData will be modified
        genRepeatCode( inputData );

        // Create a iterator to read through all the keywords to be replaced
        QMapIterator<QString,QString> iteratorkey( m_Autocode );

        // Iterate through the keywords & autocode...
        while( iteratorkey.hasNext() )
        {
            iteratorkey.next();

            // Replace any keyword with the apropriate data
            inputData.replace( iteratorkey.key(), iteratorkey.value().toUtf8() );
        }

        // Write the resulting data to the output file.
        output.write( inputData );
    }
    else
    {
        // Unable to read the file, this is a fatal error.
        std::cerr << "Unable to read " << qPrintable( input.fileName() )
                  << std::endl;
        return false;
    }

    // Close the input and the output files.
    input.close();
    output.close();

    return true;
}

/*!
 * \brief hash Fowler-Noll-Vo Hashing algorithm. This algorithm was created
 * with human readable strings in mind. The result is a XOR fold of the actual
 * hash
 * \param data The data to calculate the hash.
 * \return returns the XOR folded hash
 */
int32_t Autogen::hash( const QString &data )
{
    // Prime used for the FNV algorithm
    const int64_t FNVPrime = 1099511628211;

    // hash to calculate
    int64_t hash = 1;

    // Byte array of the string data
    QByteArray toHash( data.toUtf8() );

    // Hash in each byte of the QByteArray
    for( int i = 0; i < toHash.size(); ++i )
    {
        hash = hash * FNVPrime;
        hash = hash ^ toHash[ i ];
    }

    // Return the XOR fold of the hash
    return hash ^ ( hash >> 32 );
}

/*!
 * \brief Autogen::genRepeatCode
 * \param inputData
 */
void Autogen::genRepeatCode( QByteArray &inputData )
{
    // The start and stop keywords which define the template repeat block
    const QString StartKeyWord( "__REPEAT_START__" );
    const QString EndKeyWord( "__REPEAT_END__" );

    // Fill any repeat locations with the following
    QRegExp repeatExp( StartKeyWord + "(.*)" + EndKeyWord );

    // Set the regular expression to be non-greedy
    repeatExp.setMinimal( true );

    // Variable to capture the index locatons of the start and stop
    // of the repeat block.
    int start, end;

    do
    {
        // Get the index of the start of the Repeate block keyword
        start = inputData.indexOf( StartKeyWord );

        // Search for the end of line that comes after the start keyword
        int newline = inputData.indexOf( "\n", start );

        // Verify the operation was successful
        if( ( start > -1 ) && ( newline > -1 ) )
        {
            // Remove the entiere line containing the keyword.
            // Start index will still be valid.
            inputData.remove( start, newline - start + 1 );
        }
        else if( start > -1 )
        {
            std::cerr << "__REPEAT_START__ keyword was not followed by a newline." << std::endl;
            exit( -1 );
        }

        // Get the index of the end of the Repeate block keyword
        end = inputData.indexOf( EndKeyWord );

        // Search for the end of line that comes after the end keyword
        newline = inputData.indexOf( "\n", end );

        // Verify the operation was successful
        if( ( end > -1 ) && ( newline > -1 ) )
        {
            // Remove the entire line containing the keyword
            // end index will still be valid.
            inputData.remove( end, newline - end + 1 );
        }
        else if( end > -1 )
        {
            std::cerr << "__REPEAT_START__ keyword was not followed by a newline." << std::endl;
            exit( -1 );
        }

        if( ( start > -1 ) && ( end > -1 ) && ( end > start ) )
        {

            // Copy out the template for the repeate code
            const QString repeatTemplate =
                    QString( inputData.mid( start, end - start ) ).remove( StartKeyWord );


            // String to contain the repeateCode that is being generated
            QString repeatCode;

            // Iterator for cycling through the list of messages that have been found
            QMapIterator<QString,int32_t> iterator( m_messages );

            int repeatloop = 0;

            // Iterate through the list...
            while( iterator.hasNext() )
            {
                iterator.next();

                // Append the repeatTemplate code to the repeateCode
                repeatCode.append( repeatTemplate );

                // Replace the KeyWord, "__KEY__", with the iterator Key
                repeatCode.replace( "__KEY__", iterator.key().toUtf8() );

                // Replace the KeyWord, "__VALUE__" with the all caps
                // version of the Key (this is an enumeration)
                repeatCode.replace( "__VALUE__", iterator.key().toUpper().toUtf8() );

                if( iterator.hasNext() )
                {
                    // Append a newline between loops for readability
                    repeatCode.append( "\n" );

                    if( m_verbose )
                    {
                        // Insert a informational comment for help in debuging when
                        // writing the autogen code
                        repeatCode.append( "// Repeatblock: loop number" +
                                           QString::number( ++repeatloop ) + "\n" );
                    }
                }
            }

            if( m_verbose )
            {
                // Insert a informational comment for help in debuging when
                // writing the autogen code
                repeatCode.prepend( "// Repeatblock: Start\n" );
                repeatCode.append( "// Repeatblock: End\n" );
            }

            // Replace the repeat block (including the keywords)
            inputData.replace( start, end - start, qPrintable( repeatCode ) );
        }
    }
    while( ( start > -1 ) && ( end > -1 ) );
}
