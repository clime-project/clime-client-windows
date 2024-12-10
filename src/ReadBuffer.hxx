//------------------------------------------------------------------------------
//
// ReadBuffer.hxx
//
//------------------------------------------------------------------------------
#ifndef READBUFFER_HXX__
#define READBUFFER_HXX__

#include "Types.hxx"

#include <stdint.h>

namespace clime {

    class ReadBuffer {
    private:
        static constexpr uint32_t INITIAL_BUFLEN = 256;
        static constexpr const char* DELIMS = " \t\n";
    public:
        ReadBuffer();
        ReadBuffer( ReadBuffer& ) = delete;
        ~ReadBuffer();
        ReadBuffer& operator=( ReadBuffer& ) = delete;
    public:
        inline uint32_t Length() const { return m_length; }
        inline char_t LookAhead() const { return m_pBuf[m_current]; }
        inline bool NoMore() const { return m_length <= m_current ||
                (m_current+1 == m_length
                 && m_pBuf[m_current] == '\n'); }
        inline char GetChar() const { return m_pBuf[m_current++]; }
    public:
        bool ReadFrom( int fd );
        void GetWholeRest( range_t& rng ) const;
    public:
        template <typename T> inline bool GetNext( T& t ) const;
        template <typename T> inline bool GetRest( T& t ) const;
        template <typename T, typename... Ts>
        inline bool GetRest( T& t, Ts&&... params ) const;
    public:
        template <typename T> inline bool GetNext2( T& t, char_t delim ) const;
    private:
        bool GetNextImp( range_t& rng ) const;
        bool GetNext2Imp( range_t& rng, char_t delim ) const;
        void ExpandBuffer();
    private:
        char_t*          m_pBuf;
        uint32_t         m_capacity;
        uint32_t         m_length;
        mutable uint32_t m_current;
    };

    const ReadBuffer& operator>>( const ReadBuffer& rb, int&      n );
    const ReadBuffer& operator>>( const ReadBuffer& rb, uint32_t& n );
    const ReadBuffer& operator>>( const ReadBuffer& rb, char&     c );
    const ReadBuffer& operator>>( const ReadBuffer& rb, string_t& s );


    //--------------------------------------------------------------------------
    //
    // template inline implementation of class ReadBuffer
    //
    //--------------------------------------------------------------------------
    template <typename T>
    inline bool ReadBuffer::GetNext( T& t ) const {
        range_t rng;
        if( this->GetNext( rng ) == false )
            return false;
        t = T{ rng.first, rng.second };
        return true;
    }
    template <>
    inline bool ReadBuffer::GetNext<range_t>( range_t& rng ) const {
        return GetNextImp( rng );
    }

    template <typename T>
    inline bool ReadBuffer::GetRest( T& t ) const {
        if( NoMore() ) return false;
        *this >> t;
        return NoMore();
    }

    template <typename T, typename... Ts>
    inline bool ReadBuffer::GetRest( T& t, Ts&&... params ) const {
        if( NoMore() ) return false;
        *this >> t;
        return GetRest( std::forward<Ts>(params)... );
    }

    template <typename T>
    inline bool ReadBuffer::GetNext2( T& t, char_t delim ) const {
        range_t rng;
        if( this->GetNext2( rng, delim ) == false )
            return false;
        t = T{ rng.first, rng.second };
        return true;
    }
    template <>
    inline bool ReadBuffer::GetNext2<range_t>( range_t& rng, char_t delim ) const {
        return GetNext2Imp( rng, delim );
    }


} // namespace clime

#endif // READBUFFER_HXX__
