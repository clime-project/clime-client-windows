//------------------------------------------------------------------------------
//
// Utilities.hxx
//
//------------------------------------------------------------------------------
#ifndef UTILITIES_HXX__
#define UTILITIES_HXX__

#include <string.h>

template <int N, typename T> 
inline constexpr unsigned int countof( T const (&)[N] ) { 
    return N; 
}

template <typename CT> inline int StrLen( const CT* p ) {
    return ::strlen( (const char*)p );
}

template <typename CT1, typename CT2>
inline CT1* StrCpy( CT1* pBuf, const CT2* p ) {
    return (CT1*)::strcpy( (char*)pBuf, (const char*)p );
}

template <typename CT1, typename CT2>
inline CT1* StrNCpy( CT1* pBuf, const CT2* p, int n ) {
    return (CT1*)::strncpy( (char*)pBuf, (const char*)p, n );
}

template <typename CT1, typename CT2>
inline CT1* StrCat( CT1* pBuf, const CT2* p ) {
    return (CT1*)::strcat( (char*)pBuf, (const char*)p );
}

template <typename CT1, typename CT2>
inline int StrCmp( CT1* p1, const CT2* p2 ) {
    return ::strcmp( (const char*)p1, (const char*)p2 );
}

template <typename CT1, typename CT2>
inline int StrNCmp( CT1* p1, const CT2* p2, int n ) {
    return ::strncmp( (const char*)p1, (const char*)p2, n );
}


#endif // UTILITIES_HXX__
