//------------------------------------------------------------------------------
//
// DictionaryInfo.cxx
//
//------------------------------------------------------------------------------
#include "DictionaryInfo.hxx"

#include "ReadBuffer.hxx"
#include "WriteBuffer.hxx"

#include <ostream>
#include <cstring>
#include <algorithm>

namespace clime {

    using Kind = DictionaryKind;
    using Type = DictionaryType;

    template <typename T> bool StringTo( T& place, const char* p1, const char* p2 = nullptr );
    template <> bool StringTo<Kind>( Kind& place, const char* p1, const char* p2 );
    template <> bool StringTo<Type>( Type& place, const char* p1, const char* p2 );

    //--------------------------------------------------------------------------
    //
    // implementation of DictionaryKind
    //
    //--------------------------------------------------------------------------
    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryKind& dk ) {
        char c;
        rb >> c;
        dk = (DictionaryKind)c;
        if( rb.NoMore() == false && rb.LookAhead() == '\t' )
            rb.GetChar();
        return rb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryKind& dk ) {
        wb << (char)dk;
        return wb;
    }

    std::ostream& operator<<( std::ostream& os, const DictionaryKind& dk ) {
        switch( dk ) {
        case DictionaryKind::STANDARD:   os << "STANDARD";   break;
        case DictionaryKind::LOCATION:   os << "LOCATION";   break;
        case DictionaryKind::PERSONNAME: os << "PERSONNAME"; break;
        }
        return os;
    }


    //--------------------------------------------------------------------------
    //
    // implementation of DictionaryType
    //
    //--------------------------------------------------------------------------
    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryType& dt ) {
        char c;
        rb >> c;
        dt = (DictionaryType)c;
        if( rb.NoMore() == false && rb.LookAhead() == '\t' )
            rb.GetChar();
        return rb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryType& dt ) {
        wb << (char)dt;
        return wb;
    }

    std::ostream& operator<<( std::ostream& os, const DictionaryType& dt ) {
        switch( dt ) {
        case DictionaryType::LOOKUP: os << "LOOKUP"; break;
        case DictionaryType::TEXT:   os << "TEXT";   break;
        case DictionaryType::USER:   os << "USER";   break;
        case DictionaryType::LEARN:  os << "LEARN";  break;
        }
        return os;
    }


    //--------------------------------------------------------------------------
    //
    // implementation of DictionaryInfo
    //
    //--------------------------------------------------------------------------
    DictionaryInfo::DictionaryInfo() : title( string_t{} ),
                                       fileName( string_t{} ),
                                       kind( DictionaryKind{} ),
                                       type( DictionaryType{} ) {
    }

    DictionaryInfo::DictionaryInfo( string_t t, string_t f,
                                    DictionaryKind dk, DictionaryType dt ) : title( t ),
                                                                             fileName( f ),
                                                                             kind( dk ),
                                                                             type( dt ) {
    }

    DictionaryInfo::DictionaryInfo( const DictionaryInfo& info ) : title( info.title ),
                                                                   fileName( info.fileName ),
                                                                   kind( info.kind ),
                                                                   type( info.type ) {
    }

    DictionaryInfo& DictionaryInfo::operator=( const DictionaryInfo& info ) {
        this->title    = info.title;
        this->fileName = info.fileName;
        this->kind     = info.kind;
        this->type     = info.type;
        return *this;
    }

    bool DictionaryInfo::Parse( const char* pData,
                                string_t& title, string_t& fileName,
                                DictionaryKind& kind, DictionaryType& type ) {
        auto pEnd = pData + ::strlen( pData );
        if( 3 != std::count( pData, pEnd, ':' ) )
            return false;
        auto pDelim1 = std::find( pData,       pEnd, ':' );
        auto pDelim2 = std::find( pDelim1 + 1, pEnd, ':' );
        auto pDelim3 = std::find( pDelim2 + 1, pEnd, ':' );
        Kind k;
        Type t;
        if( !StringTo<Kind>( k, pDelim2 + 1, pDelim3 ) )
            return false;
        if( !StringTo<Type>( t, pDelim3 + 1, pEnd    ) )
            return false;
        title = string_t{ pData, pDelim1 };
        fileName = string_t{ pDelim1 + 1, pDelim2 };
        kind = k;
        type = t;
        return true;
    }

    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryInfo& info ) {
        rb >> info.title >> info.fileName >> info.kind >> info.type;
        return rb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryInfo& info ) {
        wb << info.title.c_str() << delim
           << info.fileName.c_str() << delim
           << info.kind << delim
           << info.type;
        return wb;
    }

    //--------------------------------------------------------------------------
    //
    // implementation of local functions
    //
    //--------------------------------------------------------------------------
    template <>
    bool StringTo<Kind>( Kind& place, const char* p1, const char* p2 ) {
        if( !p2 )
            p2 = p1 + ::strlen( p1 );
        auto len = p2 - p1;
        if( !len )
            return false;
        Kind tmp{};
        if( len == 8 && !::strncmp( p1, "STANDARD", 8 ) )
            tmp = Kind::STANDARD;
        else if( len == 8 && !::strncmp( p1, "LOCATION", 8 ) )
            tmp = Kind::LOCATION;
        else if( len == 10 && !::strncmp( p1, "PERSONNAME", 10 ) )
            tmp = Kind::PERSONNAME;
        else
            return false;
        place = tmp;
        return true;
    }

    template <>
    bool StringTo<Type>( Type& place, const char* p1, const char* p2 ) {
        if( !p2 )
            p2 = p1 + ::strlen( p1 );
        auto len = p2 - p1;
        if( !len )
            return false;
        Type tmp{};
        if( len == 6 && !::strncmp( p1, "LOOKUP", 6 ) )
            tmp = Type::LOOKUP;
        else if( len == 4 && !::strncmp( p1, "TEXT", 4 ) )
            tmp = Type::TEXT;
        else if( len == 4 && !::strncmp( p1, "USER", 4 ) )
            tmp = Type::USER;
        else if( len == 5 && !::strncmp( p1, "LEARN", 5 ) )
            tmp = Type::LEARN;
        else
            return false;
        place = tmp;
        return true;
    }


}

