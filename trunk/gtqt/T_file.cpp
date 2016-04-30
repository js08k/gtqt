#include "file.h"

#include <QDebug>

/*!
 * \brief TcpSocket::TcpSocket Constructor which connects the signal from
 * the Socket parent class. The signal is strictly a passthrough signal.
 * \param parent
 */
__NAMESPACE__::File::File(QObject *parent)
    : QObject( parent )
    , m_file( NULL )
{
    // Generate a new QTcpSocket with this as the parent
    m_file = new QFile( this );

    // Connect the socket's readyRead signal to receiveTcp
//    connect( m_tcpSocket, SIGNAL(readyRead()), SLOT( receiveTcp() ) );
}

__NAMESPACE__::File::File( QFile* file )
    : QObject( file )
    , m_file( file )
{
    // Connect the socket's readyRead signal to receiveTcp
//    connect( tcpSocket, SIGNAL(readyRead()), SLOT( receiveTcp() ) );
}

/*!
 * \brief TcpSocket::~TcpSocket
 */
__NAMESPACE__::File::~File()
{
    delete m_file;
}

/*!
 * \brief TcpSocket::receiveTcp
 */
void __NAMESPACE__::File::read()
{
    // Ensure at least the size of the header exists to be read
    while( m_file->bytesAvailable() >= 8 )
    {
        // Create a hear to inspect the incoming packet
        int32_t header[2];

        // Peek the header information from the packet
        m_file->peek( (char *)header, 8 );

        if( header[0] + 8 <= m_file->bytesAvailable() )
        {
            // Read in the message including the message's header
            QByteArray array = m_file->read( header[0] + 8 );

            // Pass the message to the parser
            parse( array );
        }
        else
        {
            qDebug() << "File: Discarding data, file was in error.";
            m_file->readAll();
            break;
        }
    }
}

__REPEAT_START__
void __NAMESPACE__::File::signal_receive( const __NAMESPACE__::DataPackage<__NAMESPACE__::__KEY__> data ) const
{
    emit read( data );
}
__REPEAT_END__

void __NAMESPACE__::File::signal_malformed() const
{
    emit malformed();
}
