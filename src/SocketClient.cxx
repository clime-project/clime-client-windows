//------------------------------------------------------------------------------
//
// SocketClient.cxx
//
//------------------------------------------------------------------------------
#include "SocketClient.hxx"
#include "ReadBuffer.hxx"
#include "WriteBuffer.hxx"

#include <string.h>
#include <netdb.h>    // for ::getnostbyname
#include <unistd.h>
#include <stdexcept>

namespace clime {

    SocketClient::SocketClient( const char* pSrvName,
                                uint32_t portNumber ) : m_socket( 0 ),
                                                        m_pReadBuf(  new ReadBuffer{} ),
                                                        m_pWriteBuf( new WriteBuffer{} ) {

        hostent* pHost = ::gethostbyname( pSrvName );
        if( !pHost )
            throw std::runtime_error( "::gethostbyname() failed." );

        struct in_addr hp_addr;
        ::memcpy( &hp_addr, pHost->h_addr, pHost->h_length );

        struct sockaddr_in sin;
        ::memset( &sin, 0, sizeof(sin) );
        sin.sin_family = AF_INET;
        sin.sin_addr = hp_addr;
        sin.sin_port = htons( portNumber ); 

        int sock = ::socket( AF_INET, SOCK_STREAM, 0 );
        if( sock < 0 )
            throw std::runtime_error( "::socket() failed." );

        if( ::connect( sock, (const sockaddr*)&sin, sizeof(sin) ) < 0 )
            throw std::runtime_error( "::connect() failed." );

        m_socket = sock;
    }

    SocketClient::~SocketClient() {
        ::close( m_socket );
        delete m_pReadBuf;
        delete m_pWriteBuf;
    }


}  // namespace clime
