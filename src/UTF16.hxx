//------------------------------------------------------------------------------
//
// UTF16.hxx
//
//------------------------------------------------------------------------------
#ifndef UTF16_HXX__
#define UTF16_HXX__

#include "Types.hxx"

#include <stdint.h>

namespace clime {

    class UTF16 {
    public:
        static inline bool IsSurrogatePair( const wchar_t* p ) {
            return ((p[0] & 0xFC00u) == 0xD800u)
                && ((p[1] & 0xFC00u) == 0xDC00u);
        }
        static inline const wchar_t* GetCodePoint( const wchar_t* p,
                                                   uint32_t& val ) {
            if( IsSurrogatePair( p ) ) {
                val = (((p[0] & 0x03FFu) << 10) | (p[1] & 0x03FFu)) + 0x10000;
                return p + 2;
            } else {
                val = *p;
                return p + 1;
            }
        }
        static inline const wchar_t* Increment( const wchar_t* pCur ) {
            return pCur + (IsSurrogatePair( pCur ) ? 2 : 1);
        }
        static inline const wchar_t* Decrement( const wchar_t* pTop,
                                                const wchar_t* pCur ) {
            (void)pTop;
            return pCur - (IsSurrogatePair( pCur - 2 ) ? 2 : 1);
        }
    public:
        static bool FromUtf8( const range_t& rng,
                              bool (*pReceiver)(const wchar_t*, const wchar_t*) );
        static bool ToUtf8( const wchar_t* pUnicode, char* pBuf, uint32_t& bufLen );
    };

} // namespace clime

#endif // UTF16_HXX__
