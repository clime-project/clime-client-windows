//------------------------------------------------------------------------------
//
// SearchResult.hxx
//
//------------------------------------------------------------------------------
#ifndef SEARCHRESULT_HXX__
#define SEARCHRESULT_HXX__

#include "Common.hxx"

#include <stdint.h>
#include <utility>
#include <vector>

namespace clime {

    class SearchResult {
    private:
        using EntryT     = std::pair<string_t,string_t>;  // pattern & word
        using ContainerT = std::vector<EntryT>;
    public:
        SearchResult() = delete;
        SearchResult( uint32_t limit );
        SearchResult( const SearchResult& ) = delete;
        ~SearchResult();
        SearchResult& operator=( const SearchResult& ) = delete;
    public:
        inline uint32_t Size() const { return m_entries.size(); }
        inline uint32_t Limit() const { return m_limit; }
        inline uint32_t Rest() const { return m_limit - m_entries.size(); }
        inline bool IsFull() const { return ( m_entries.size() == m_limit ); }
        inline void Clear() { m_entries.clear(); }
        inline const EntryT& operator[]( uint32_t idx ) const { return m_entries[idx]; }
        template <typename FNC>
        inline void EnumResults( const FNC& fnc ) const {
            for( const auto& entry : m_entries )
                fnc( entry.first, entry.second );
        }
    public:
        bool AddEntry( const char_t* pPattern, const char_t* pWord );
    private:
        uint32_t    m_limit;
        ContainerT  m_entries;
    };


}  // namespace clime

#endif // SEARCHRESULT_HXX__

