//------------------------------------------------------------------------------
//
// Colors.hxx
//
//------------------------------------------------------------------------------
#ifndef COLORS_HXX__
#define COLORS_HXX__

#include <stdint.h>

namespace clime {

    class Colors {
    public:
        Colors() = delete;
        Colors( const Colors& ) = delete;
        ~Colors() = delete;
        Colors& operator=( const Colors& ) = delete;
    public:
        static int32_t Create( const wchar_t* pNameOrCode );
        static int32_t Create( uint8_t r, uint8_t g, uint8_t b );
    };

} // namespace clime

#endif // COLORS_HXX__
