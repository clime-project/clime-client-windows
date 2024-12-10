//------------------------------------------------------------------------------
//
// UTF16.cxx
//
//------------------------------------------------------------------------------
#include "UTF16.hxx"

#include "WinAPI.hxx"

namespace clime {

    static wchar_t s_unicodeBuf[4096];

    bool UTF16::FromUtf8( const range_t& rng,
                          bool (*pReceiver)(const wchar_t*, const wchar_t*) ) {
        s_unicodeBuf[0] = 0;
        uint32_t cnt = 0;
        uint32_t len = rng.second - rng.first;
        if( !len ) {
            if( pReceiver )
                (*pReceiver)( s_unicodeBuf, s_unicodeBuf + 0 );
            return true;
        }
        LPCSTR pData = reinterpret_cast<LPCSTR>( rng.first );
//      //最後のパラメータに０を渡して一度コールし、必要なバッファ文字数を知る
//      cnt = WinAPI::MultiByteToWideChar( CP_UTF8, MB_PRECOMPOSED,
//                                         pData, len, s_unicodeBuf, 0 );
//      if( sizeof(s_unicodeBuf) < cnt )
//          return false;
        cnt = WinAPI::MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS,
                                           pData, len,
                                           s_unicodeBuf, sizeof(s_unicodeBuf) );
        if( !cnt )
            return false;
        s_unicodeBuf[cnt] = 0;
        if( pReceiver )
            (*pReceiver)( s_unicodeBuf, s_unicodeBuf + cnt );
        return true;
    }
    bool UTF16::ToUtf8( const wchar_t* pUnicode, char* pBuf, uint32_t& bufLen ) {
        pBuf[0] = 0;
        uint32_t len = ::wcslen( pUnicode );
        if( !len ) {
            bufLen = 0;
            return true;
        }
        int byteLen = WinAPI::WideCharToMultiByte( CP_UTF8, 0, //WC_ERR_INVALID_CHARS,
                                                   pUnicode, len, pBuf, bufLen, NULL, NULL );
        if( !byteLen )
            return false;
        pBuf[byteLen] = 0;
        bufLen = byteLen;
        return true;
    }

}  // namespace clime
