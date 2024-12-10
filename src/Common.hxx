//------------------------------------------------------------------------------
//
// Common.hxx
//
//------------------------------------------------------------------------------
#ifndef COMMON_HXX__
#define COMMON_HXX__

#include "Types.hxx"

namespace clime {

    class Constants {
    public:
        static constexpr int DEFAULT_SERVER_PORT     = 1178;
        static constexpr int DEFAULT_CANDIDATE_COUNT = 40;
        static constexpr int MAXWORDLEN              = 200;
    };

    enum class KbdType {
        KB_101 = 101,
        KB_106 = 106
    };

    enum class BoxType {
        FLAT    = 0,
        SUNKEN  = 1,
        RAISED  = 2,
        ETCHED  = 3
    };

    enum class CursorType {
        BLOCK       = 0,
        LINE        = 1,
        UNDERSCORE  = 2
    };

    constexpr const wchar_t*  APPNAME   = L"winclime";
    constexpr const wchar_t*  HELPPAGE  = L"README.htm";

} // namespace clime

#endif // COMMON_HXX__
