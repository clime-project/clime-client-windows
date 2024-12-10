//------------------------------------------------------------------------------
//
// EngineProxy.cxx
//
//------------------------------------------------------------------------------
#include "EngineProxy.hxx"

#include "EngineInfo.hxx"
#include "SocketClient.hxx"
#include "DictionaryInfo.hxx"
#include "ReadBuffer.hxx"
#include "WriteBuffer.hxx"
#include "RequestID.hxx"
#include "ResponseID.hxx"
#include "UTF16.hxx"

#include <cstring>

namespace clime {

    static char  s_utf8Buf1[1024];
    static char  s_utf8Buf2[3072];
    static const EngineProxy::StringReceiver* s_pReceiver = nullptr;

    static bool ReceiveUtf16Proxy( const wchar_t* p1, const wchar_t* p2 );
    static bool ExecSearchImpl( const char* pPattern,
                                bool bExact, SocketClient* pSockClient );
    static bool GetVersionImpl( SocketClient* pSockClient );
//  static bool GetHostNameImpl( SocketClient* pSockClient );
    static bool SetContextImpl( const char* pContext, SocketClient* pSockClient );
    static bool RegWordImpl( const char* pPattern,
                             const char* pWord, SocketClient* pSockClient );
    static bool DelWordImpl( const char* pWord, SocketClient* pSockClient );

    //--------------------------------------------------------------------------
    //
    // implementation of EngineProxy
    //
    //--------------------------------------------------------------------------
    EngineProxy::EngineProxy( const EngineInfo& info )
        : m_pSockClient( new SocketClient{ info.ServerName().c_str(),
                info.PortNumber() } ) {
    }

    EngineProxy::~EngineProxy() {
        delete m_pSockClient;
    }

    bool EngineProxy::Disconnect() {
        int sock = m_pSockClient->GetSocket();
        auto& rb = m_pSockClient->GetReadBuf();
        auto& wb = m_pSockClient->GetWriteBuf();
        wb << RequestID::DISCONNECT;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    bool EngineProxy::ExecSearch( const wchar_t* pPattern,
                                  bool bExact, const StringReceiver& rcv ) {
        // pPattern を wchar_t から UTF-8 に変換する
        uint32_t len = sizeof(s_utf8Buf1);
        if( !UTF16::ToUtf8( pPattern, s_utf8Buf1, len ) )
            return false;
        s_pReceiver = &rcv;
        bool ret = ExecSearchImpl( s_utf8Buf1, bExact, m_pSockClient );
        s_pReceiver = nullptr;
        return ret;
    }

    bool EngineProxy::ExecSearchNext( const StringReceiver& rcv ) {
        s_pReceiver = &rcv;
        bool ret = ExecSearchImpl( NULL, false, m_pSockClient );
        s_pReceiver = nullptr;
        return ret;
    }

    bool EngineProxy::GetVersion( const StringReceiver& rcv ) {
        s_pReceiver = &rcv;
        bool ret = GetVersionImpl( m_pSockClient );
        s_pReceiver = nullptr;
        return ret;
    }

//  bool EngineProxy::GetHostName( const StringReceiver& rcv ) {
//      s_pReceiver = &rcv;
//      bool ret = GetHostNameImpl( m_pSockClient );
//      s_pReceiver = nullptr;
//      return ret;
//  }

    bool EngineProxy::ClearContext() {
        int sock = m_pSockClient->GetSocket();
        auto& rb = m_pSockClient->GetReadBuf();
        auto& wb = m_pSockClient->GetWriteBuf();
        wb << RequestID::CLEARCONTEXT;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    bool EngineProxy::SetContext( const wchar_t* pContext ) {
        // pContext を wchar_t から UTF-8 に変換する
        uint32_t len = sizeof(s_utf8Buf2);
        if( !UTF16::ToUtf8( pContext, s_utf8Buf2, len ) )
            return false;
        return SetContextImpl( s_utf8Buf2, m_pSockClient );
    }

    bool EngineProxy::RegWord( const wchar_t* pPattern, const wchar_t* pWord ) {
        // pPattern / pWord を wchar_t から UTF-8 に変換する
        uint32_t len = sizeof(s_utf8Buf1);
        if( !UTF16::ToUtf8( pPattern, s_utf8Buf1, len ) )
            return false;
        len = sizeof(s_utf8Buf2);
        if( !UTF16::ToUtf8( pWord, s_utf8Buf2, len ) )
            return false;
        return RegWordImpl( s_utf8Buf1, s_utf8Buf2, m_pSockClient );
    }

    bool EngineProxy::DelWord( const wchar_t* pWord ) {
        // pWord を wchar_t から UTF-8 に変換する
        uint32_t len = sizeof(s_utf8Buf1);
        if( !UTF16::ToUtf8( pWord, s_utf8Buf1, len ) )
            return false;
        return DelWordImpl( s_utf8Buf1, m_pSockClient );
    }

    bool EngineProxy::SaveDict() {
        int sock = m_pSockClient->GetSocket();
        auto& rb = m_pSockClient->GetReadBuf();
        auto& wb = m_pSockClient->GetWriteBuf();
        wb << RequestID::SAVEDICT;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    bool EngineProxy::NotifySelection( int index ) {
        int sock = m_pSockClient->GetSocket();
        auto& rb = m_pSockClient->GetReadBuf();
        auto& wb = m_pSockClient->GetWriteBuf();
        wb << RequestID::NOTIFYSELECTION << index;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    bool EngineProxy::SetCandidateLimit( uint32_t limit ) {
        int sock = m_pSockClient->GetSocket();
        auto& rb = m_pSockClient->GetReadBuf();
        auto& wb = m_pSockClient->GetWriteBuf();
        wb << RequestID::SETCANDLIMIT << limit;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

//  bool EngineProxy::EnumDictionary( const StringReceiver& rcv ) {
//      int sock = m_pSockClient->GetSocket();
//      auto& rb = m_pSockClient->GetReadBuf();
//      auto& wb = m_pSockClient->GetWriteBuf();
//      wb << RequestID::ENUMDICTIONARY;
//      if( wb.FlushTo( sock ) == false )
//          return false;
//
//      if( rb.ReadFrom( sock ) == false )
//          return false;
//      ResponseID res;
//      rb >> res;
//      if( res != ResponseID::COMPLETE )
//          return false;
//      if( rb.LookAhead() == '\t' )
//          rb.GetChar();
//      range_t rng;
//      while( rb.NoMore() == false ) {
//          rb.GetNext( rng );
//          if( rcv( rng ) == false )
//              break;
//      }
//      return true;
//  }

//  bool EngineProxy::DictInfo( int index,
//                              DictionaryInfo& info, uint32_t& entryCount ) {
//      int sock = m_pSockClient->GetSocket();
//      auto& rb = m_pSockClient->GetReadBuf();
//      auto& wb = m_pSockClient->GetWriteBuf();
//      wb << RequestID::DICTIONARYINFO << index;
//      if( wb.FlushTo( sock ) == false )
//          return false;
//      if( rb.ReadFrom( sock ) == false )
//          return false;
//      ResponseID res;
//      rb >> res;
//      if( res != ResponseID::COMPLETE )
//          return false;
//      if( rb.LookAhead() == '\t' )
//          rb.GetChar();
//      rb >> info >> entryCount;
//      return ( res == ResponseID::COMPLETE && rb.NoMore() );
//  }

//  bool EngineProxy::Shutdown() {
//      int sock = m_pSockClient->GetSocket();
//      auto& wb = m_pSockClient->GetWriteBuf();
//      wb << RequestID::SHUTDOWN;
//      if( wb.FlushTo( sock ) == false )
//          return false;
//      return true;
//  }


    //--------------------------------------------------------------------------
    //
    // local functions
    //
    //--------------------------------------------------------------------------
    static bool ReceiveUtf16Proxy( const wchar_t* p1, const wchar_t* p2 ) {
        return (*s_pReceiver)( p1, p2 );
    }

    //MEMO : pPattern が NULL の場合、SearchNext(N) として扱う
    static bool ExecSearchImpl( const char* pPattern,
                                bool bExact, SocketClient* pSockClient ) {
        int sock = pSockClient->GetSocket();
        auto& rb = pSockClient->GetReadBuf();
        auto& wb = pSockClient->GetWriteBuf();
        if( !pPattern )
            wb << RequestID::EXECSEARCHNEXT;
        else
            wb << ((!bExact) ? RequestID::EXECSEARCH2S : RequestID::EXECSEARCH2X) << pPattern;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        if( res == ResponseID::NO_CANDIDATE )
            return true;
        if( res == ResponseID::ERROR )
            return false;
        char_t delim = rb.LookAhead();
        rb.GetChar();
        range_t rng;
        while( rb.NoMore() == false ) {
            rb.GetNext2( rng, delim );
            if( UTF16::FromUtf8( rng, ReceiveUtf16Proxy ) == false )
                break;
        }
        return true;
    }
    static bool GetVersionImpl( SocketClient* pSockClient ) {
        int sock = pSockClient->GetSocket();
        auto& rb = pSockClient->GetReadBuf();
        auto& wb = pSockClient->GetWriteBuf();
        wb << RequestID::GETVERSION;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        //MEMO : RequestID::GETVERSION のレスポンスでは先頭に ResponseID がつかない
        range_t rng;
        rb.GetNext( rng );
        UTF16::FromUtf8( rng, ReceiveUtf16Proxy );
        return true;
    }
//  static bool GetHostNameImpl( SocketClient* pSockClient ) {
//      int sock = pSockClient->GetSocket();
//      auto& rb = pSockClient->GetReadBuf();
//      auto& wb = pSockClient->GetWriteBuf();
//      wb << RequestID::GETHOSTNAME;
//      if( wb.FlushTo( sock ) == false )
//          return false;
//      if( rb.ReadFrom( sock ) == false )
//          return false;
//      //MEMO : RequestID::GETHOSTNAME のレスポンスでは先頭に ResponseID がつかない
//      range_t rng;
//      rb.GetNext( rng );
//      UTF16::FromUtf8( rng );
//      return true;
//  }

    static bool SetContextImpl( const char* pContext, SocketClient* pSockClient ) {
        int sock = pSockClient->GetSocket();
        auto& rb = pSockClient->GetReadBuf();
        auto& wb = pSockClient->GetWriteBuf();
        wb << RequestID::SETCONTEXT << pContext;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    static bool RegWordImpl( const char* pPattern,
                             const char* pWord, SocketClient* pSockClient ) {
        static const char* DELIMS = "|,!#$%&'*+-./:=?^_`~\"";
        char delim = '\0';
        for( const char* p = DELIMS; !!*p; ++p ) {
            char ch = *p;
            if( !::strchr( pPattern, ch ) && !::strchr( pWord, ch ) ) {
                delim = ch;
                break;
            }
        }
        int sock = pSockClient->GetSocket();
        auto& rb = pSockClient->GetReadBuf();
        auto& wb = pSockClient->GetWriteBuf();
        wb << RequestID::REGWORD2 << delim << pPattern << delim << pWord;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

    static bool DelWordImpl( const char* pWord, SocketClient* pSockClient ) {
        int sock = pSockClient->GetSocket();
        auto& rb = pSockClient->GetReadBuf();
        auto& wb = pSockClient->GetWriteBuf();
        wb << RequestID::DELWORD2 << pWord;
        if( wb.FlushTo( sock ) == false )
            return false;
        if( rb.ReadFrom( sock ) == false )
            return false;
        ResponseID res;
        rb >> res;
        return ( res == ResponseID::COMPLETE && rb.NoMore() );
    }

}  // namespace clime
