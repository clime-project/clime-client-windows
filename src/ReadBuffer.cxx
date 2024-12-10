//------------------------------------------------------------------------------
//
// ReadBuffer.cxx
//
//------------------------------------------------------------------------------
#include "ReadBuffer.hxx"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <assert.h>
#include <algorithm>

namespace clime {


    ReadBuffer::ReadBuffer() : m_pBuf( nullptr ),
                               m_capacity( INITIAL_BUFLEN ),
                               m_length( 0 ),
                               m_current( 0 ) {
        m_pBuf = new char_t[m_capacity];
    }

    ReadBuffer::~ReadBuffer() {
        if( !!m_pBuf )
            delete[] m_pBuf;
    }

    bool ReadBuffer::ReadFrom( int fd ) {
        m_length = 0;
        uint32_t totalLen = 0;
        while( true ) {
            int readBytes = ::read( fd, m_pBuf + totalLen, m_capacity - totalLen );
            if( !readBytes )
                break;
            if( readBytes < 0 )
                return false;
            totalLen += readBytes;
            if( totalLen < m_capacity )
                break;
            else if( totalLen == m_capacity )
                this->ExpandBuffer();
            if( m_pBuf[totalLen-1] == '\n' )
                break;
        }
        if( 1 < totalLen && m_pBuf[totalLen-2] == '\r' && m_pBuf[totalLen-1] == '\n' )
            totalLen -= 2;
        if( !totalLen || m_pBuf[totalLen-1] != '\n' ) {
            if( totalLen == m_capacity )
                this->ExpandBuffer();
            m_pBuf[totalLen++] = '\n';
        }
        m_length = totalLen;
        m_current = 0;
        return true;
    }

    void ReadBuffer::GetWholeRest( range_t& rng ) const {
        rng.first  = m_pBuf + m_current;
        rng.second = m_pBuf + m_length;
        if( rng.second[-1] == '\n' )
            --rng.second;
    }

    bool ReadBuffer::GetNextImp( range_t& rng ) const {
        if( NoMore() )
            return false;
        rng.first  = m_pBuf + m_current;
        rng.second = m_pBuf + m_length;
        rng.second = std::find_if( rng.first, rng.second,
                                   []( char c ) -> bool {
                                       return ::strchr( DELIMS, c ) != nullptr; } );
        m_current = rng.second - m_pBuf;
        if( m_current < m_length )
            ++m_current;
        return true;
    }

    bool ReadBuffer::GetNext2Imp( range_t& rng, char_t delim ) const {
        if( NoMore() )
            return false;
        rng.first  = m_pBuf + m_current;
        rng.second = m_pBuf + m_length;
        rng.second = std::find( rng.first, rng.second, delim );
        m_current = rng.second - m_pBuf;
        if( m_current < m_length )
            ++m_current;
        return true;
    }

    void ReadBuffer::ExpandBuffer() {
        auto newCapacity = 2 * m_capacity;
        auto pNewBuf = new char_t[newCapacity];
        ::memcpy( pNewBuf, m_pBuf, m_capacity );
        if( !!m_pBuf )
            delete[] m_pBuf;
        m_pBuf = pNewBuf;
        m_capacity = newCapacity;
    }

    const ReadBuffer& operator>>( const ReadBuffer& rb, int& n ) {
        if( rb.NoMore() == false ) {
            range_t rng;
            rb.GetNext( rng );
            int tmp = 0;
            for( ; rng.first < rng.second; ++rng.first )
                tmp = (tmp * 10) + (rng.first[0] - '0');
            n = tmp;
        }
        return rb;
    }

    const ReadBuffer& operator>>( const ReadBuffer& rb, uint32_t& n ) {
        if( rb.NoMore() == false ) {
            range_t rng;
            rb.GetNext( rng );
            uint32_t tmp = 0;
            for( ; rng.first < rng.second; ++rng.first )
                tmp = (tmp * 10) + (rng.first[0] - '0');
            n = tmp;
        }
        return rb;
    }

    const ReadBuffer& operator>>( const ReadBuffer& rb, char& c ) {
        if( rb.NoMore() == false )
            c = rb.GetChar();
        return rb;
    }

    const ReadBuffer& operator>>( const ReadBuffer& rb, string_t& s ) {
        if( rb.NoMore() == false )
            rb.GetNext( s );
        return rb;
    }


} // namespace clime

