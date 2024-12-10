//------------------------------------------------------------------------------
//
// SearchResult.cxx
//
//------------------------------------------------------------------------------
#include "SearchResult.hxx"

#include <algorithm>

namespace clime {

    SearchResult::SearchResult( uint32_t limit ) : m_limit( limit ),
                                                   m_entries( ContainerT{} ) {
        m_entries.reserve( limit );
    }

    SearchResult::~SearchResult() {
        m_entries.clear();
    }

    bool SearchResult::AddEntry( const char_t* pPattern, const char_t* pWord ) {
        if( this->IsFull() )
            return false;
        auto itr = std::find_if( m_entries.begin(), m_entries.end(),
                                 [&pWord]( const EntryT& entry ) -> bool {
                                     return entry.second == pWord;
                                 } );
        if( itr == m_entries.end() )
            m_entries.emplace_back( pPattern, pWord );
        return true;
    }


}  // namespace clime

