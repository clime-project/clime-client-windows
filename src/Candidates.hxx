//------------------------------------------------------------------------------
//
// Candidates.hxx
//
//------------------------------------------------------------------------------
#ifndef CANDIDATES_HXX__
#define CANDIDATES_HXX__

#include "Types.hxx"

#include <stdint.h>

namespace clime {

    //ToDo : 現状では単語は 100 文字までで、候補リストは 1000件が上限。この恣意的な制限は撤廃したい。

    //--------------------------------------------------------------------------
    //
    // template class Candidates
    //
    //--------------------------------------------------------------------------
    class Candidates {
    private:
        static constexpr const int MAXCANDS = 1000;
    private:
        class Buffer {
        private:
            static constexpr const int CAPACITY = 100;
        public:
            Buffer();
            Buffer( const Buffer& ) = delete;
            ~Buffer();
            Buffer& operator=( const Buffer& ) = delete;
        public:
            inline uint32_t Length() const { return m_length; }
            inline wchar_t* Get() { return m_buffer; }
            inline const wchar_t* Get() const { return m_buffer; }
        public:
            bool Assign( const wchar_t* pTop, const wchar_t* pEnd );
        private:
            uint32_t m_length;
            wchar_t  m_buffer[CAPACITY];
        };
    public:
        Candidates();
        Candidates( const Candidates& ) = delete;
        ~Candidates();
        Candidates& operator=( const Candidates& ) = delete;
    public:
        inline bool IsFull() const { return m_count == MAXCANDS; }
        inline uint32_t Capacity() const { return MAXCANDS; }
        inline bool Empty() const { return m_count == 0; }
        inline uint32_t Size() const { return m_count; }
        inline uint32_t& Selection() { return m_selection; }
        inline uint32_t Selection() const { return m_selection; }
        inline void Clear() { m_count = 0; m_selection = 0; m_bNoMoreNext = false; }
        inline bool& NoMoreNext() { return m_bNoMoreNext; }
    public:
        bool Add( const wchar_t* pTop, const wchar_t* pEnd );
        uint32_t LengthOf( uint32_t index ) const;
        const wchar_t* operator[]( uint32_t index ) const;
        const wchar_t* operator*() const;  //ToDo : これはわかりにくいので、別の名前を考えるべきか。
    private:
        uint32_t    m_count;
        uint32_t    m_selection;
        Buffer      m_buffers[MAXCANDS];
        bool        m_bNoMoreNext;
    };

} // namespace clime


#endif // CANDIDATES_HXX__
