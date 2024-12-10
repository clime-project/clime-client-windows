//------------------------------------------------------------------------------
//
// WriteBuffer.cxx
//
//------------------------------------------------------------------------------
#include "WriteBuffer.hxx"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <assert.h>

namespace clime {

    Delim__ delim;



    WriteBuffer::WriteBuffer() : m_pBuf( nullptr ),
                                 m_capacity( INITIAL_BUFLEN ),
                                 m_length( 0 ) {
        m_pBuf = new char[m_capacity];
    }

    WriteBuffer::~WriteBuffer() {
        if( !!m_pBuf )
            delete[] m_pBuf;
    }

    void WriteBuffer::AddData( const char* p1, const char* p2 ) {
        auto len = p2 - p1;
        if( m_capacity < (m_length + len + 1) )    // Flush 時点で付加する \n の分を１バイトあけておく
            this->ExpandBuffer( m_length + len + 1 );
        ::strncpy( m_pBuf + m_length, p1, len );
        m_length += len;
    }

    bool WriteBuffer::FlushTo( int fd ) {
        assert( m_length < m_capacity );
        if( !m_length )
            return true;
        m_pBuf[m_length++] = '\n';
        uint32_t len = ::write( fd, m_pBuf, m_length );
        bool result = ( m_length == len );
        m_length = 0;
        return result;
    }

    void WriteBuffer::ExpandBuffer( uint32_t newLen ) {
        uint32_t newCapacity = m_capacity;
        while( newCapacity < newLen )
            newCapacity = (newCapacity << 1);
        auto pNewBuf = new char[newCapacity];
        ::memcpy( pNewBuf, m_pBuf, m_length );
        if( !!m_pBuf )
            delete[] m_pBuf;
        m_pBuf = pNewBuf;
        m_capacity = newCapacity;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, int n ) {
        char buf[32];
        ::sprintf( buf, "%d", n );
        wb.AddData( buf, buf + ::strlen( buf ) );
        return wb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, uint32_t n ) {
        char buf[32];
        ::sprintf( buf, "%u", n );
        wb.AddData( buf, buf + ::strlen( buf ) );
        return wb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, char c ) {
        char buf[2];
        buf[0] = c;
        buf[1] = '\0';
        wb.AddData( buf, buf + 1 );
        return wb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, const char* p ) {
        wb.AddData( p, p + ::strlen( p ) );
        return wb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, const Delim__& ) {
        char buf[2];
        buf[0] = '\t';
        buf[1] = '\0';
        wb.AddData( buf, buf + 1 );
        return wb;
    }

} // namespace clime

