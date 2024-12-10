//------------------------------------------------------------------------------
//
// DictionaryInfo.hxx
//
//------------------------------------------------------------------------------
#ifndef DICTIONARYINFO_HXX__
#define DICTIONARYINFO_HXX__

#include "Types.hxx"

#include <iosfwd>

namespace clime {

    class ReadBuffer;
    class WriteBuffer;

    enum class DictionaryKind : char {
        STANDARD    = '0',  // 標準辞書
        LOCATION    = '1',  // 地名辞書
        PERSONNAME  = '2'   // 人名辞書
    };

    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryKind& dk );
    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryKind& dk );
    std::ostream& operator<<( std::ostream& os, const DictionaryKind& dk );


    enum class DictionaryType {
        LOOKUP  = '0',   // ルックアップ辞書
        TEXT    = '1',   // テキスト辞書
        USER    = '2',   // ユーザー辞書
        LEARN   = '3'    // 学習辞書
    };

    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryType& dt );
    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryType& dt );
    std::ostream& operator<<( std::ostream& os, const DictionaryType& dt );


    struct DictionaryInfo {
        DictionaryInfo();
        DictionaryInfo( string_t t, string_t f,
                        DictionaryKind dk, DictionaryType dt );
        DictionaryInfo( const DictionaryInfo& info );
        DictionaryInfo& operator=( const DictionaryInfo& info );
        string_t        title;
        string_t        fileName;
        DictionaryKind  kind;
        DictionaryType  type;
    public:
        static bool Parse( const char* pData,
                           string_t& title, string_t& fileName,
                           DictionaryKind& kind, DictionaryType& type );
    };

    const ReadBuffer& operator>>( const ReadBuffer& rb, DictionaryInfo& info );
    WriteBuffer& operator<<( WriteBuffer& wb, const DictionaryInfo& info );

}

#endif // DICTIONARYINFO_HXX__

