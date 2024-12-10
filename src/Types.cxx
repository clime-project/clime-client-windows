//------------------------------------------------------------------------------
//
// Types.cxx
//
//------------------------------------------------------------------------------
#include "Types.hxx"

#include <ostream>

namespace clime {

    std::ostream& operator<<( std::ostream& os, const range_t& rng ) {
        os.write( (const char*)rng.first, rng.second - rng.first );
        return os;
    }

}

