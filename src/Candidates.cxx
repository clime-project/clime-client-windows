//------------------------------------------------------------------------------
//
// Candidates.cxx
//
//------------------------------------------------------------------------------
#include "Candidates.hxx"
#include "Utilities.hxx"

#include <algorithm>

namespace clime {

    //--------------------------------------------------------------------------
    //
    // implementation of class Candidates::Buffer
    //
    //--------------------------------------------------------------------------
    Candidates::Buffer::Buffer() : m_length( 0 ) {
        m_buffer[0] = 0;
    }

    Candidates::Buffer::~Buffer() {
    }

    bool Candidates::Buffer::Assign( const wchar_t* pTop, const wchar_t* pEnd ) {
        uint32_t cnt = pEnd - pTop;
        if( CAPACITY < cnt )
            return false;
        std::copy( pTop, pEnd, m_buffer );
        m_buffer[cnt] = 0;
        m_length = cnt;
        return true;
    }

    //--------------------------------------------------------------------------
    //
    // implementation of class Candidates
    //
    //--------------------------------------------------------------------------
    Candidates::Candidates() : m_count( 0 ),
                               m_selection( 0 ),
                               m_bNoMoreNext( false ) {
    }

    Candidates::~Candidates() {
    }

    bool Candidates::Add( const wchar_t* pTop, const wchar_t* pEnd ) {
        if( IsFull() )
            return false;
        bool ret = m_buffers[m_count].Assign( pTop, pEnd );
        if( ret )
            ++m_count;
        return ret;
    }

    uint32_t Candidates::LengthOf( uint32_t index ) const {
        if( !( index < m_count) )
            return 0;
        return m_buffers[index].Length();
    }

    const wchar_t* Candidates::operator[]( uint32_t index ) const {
        if( !( index < m_count) )
            return nullptr;
        return m_buffers[index].Get();
    }

    const wchar_t* Candidates::operator*() const {
        if( !( 1 <= m_selection && m_selection <= m_count) )
            return nullptr;
        return m_buffers[m_selection-1].Get();
    }

} // namespace clime

