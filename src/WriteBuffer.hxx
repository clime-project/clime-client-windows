//------------------------------------------------------------------------------
//
// WriteBuffer.hxx
//
//------------------------------------------------------------------------------
#ifndef WRITEBUFFER_HXX__
#define WRITEBUFFER_HXX__

#include <stdint.h>

namespace clime {

    class Delim__ {};
    extern Delim__ delim;

    class WriteBuffer {
    private:
        static constexpr uint32_t INITIAL_BUFLEN = 256;
    public:
        WriteBuffer();
        WriteBuffer( WriteBuffer& ) = delete;
        ~WriteBuffer();
        WriteBuffer& operator=( WriteBuffer& ) = delete;
    public:
        void AddData( const char* p1, const char* p2 );
        bool FlushTo( int fd );
    private:
        void ExpandBuffer( uint32_t newLen );
    private:
        char*       m_pBuf;
        uint32_t    m_capacity;
        uint32_t    m_length;
    };

    WriteBuffer& operator<<( WriteBuffer& wb, int n );
    WriteBuffer& operator<<( WriteBuffer& wb, uint32_t n );
    WriteBuffer& operator<<( WriteBuffer& wb, char c );
    WriteBuffer& operator<<( WriteBuffer& wb, const char* p );
    WriteBuffer& operator<<( WriteBuffer& wb, const Delim__& d );


    inline WriteBuffer& operator<<( WriteBuffer& wb, const unsigned char* p ) {
        wb << (const char*)p;
        return wb;
    }


} // namespace clime

#endif // WRITEBUFFER_HXX__
