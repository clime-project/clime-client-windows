//------------------------------------------------------------------------------
//
// Types.hxx
//
//------------------------------------------------------------------------------
#ifndef TYPES_HXX__
#define TYPES_HXX__

#include <string>
#include <utility>
#include <iosfwd>

namespace clime {

    #define S(str) ((const char_t*)(str))

    using char_t   = unsigned char;
    using string_t = std::basic_string<char_t>;
    using range_t  = std::pair<const char_t*, const char_t*>;


    std::ostream& operator<<( std::ostream& os, const range_t& rng );

}

#endif // TYPES_HXX__

