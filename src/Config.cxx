//------------------------------------------------------------------------------
//
// Config.cxx
//
//------------------------------------------------------------------------------
#include "Config.hxx"

#include "Utilities.hxx"
#include "EngineInfo.hxx"

#include "IniFile.hxx"
#include "Colors.hxx"
#include "ColorTheme.hxx"
#include "WinAPI.hxx"

#include <cstring>
#include <wchar.h>
#include <vector>
#include <algorithm>


namespace clime {

    //[Engine]
    constexpr const wchar_t* DEFAULT_SERVERNAME       = L"localhost";
    constexpr int            DEFAULT_SERVERPORT       = 1178;
    constexpr uint32_t       DEFAULT_CANDMAX          = 40;
    //[SendMethod]
    constexpr const wchar_t* DEFAULT_SENDMETHOD       = L"Ctrl+V";
    //[Behavior]
    constexpr int            DEFAULT_KBDTYPE          = 106;
    constexpr bool           DEFAULT_EMACSKEYBIND     = false;
    constexpr bool           DEFAULT_FWDEMACSKEY      = false;
    constexpr bool           DEFAULT_PREDICTAFTERFIX  = false;
    constexpr bool           DEFAULT_INDEXING         = false;
    constexpr bool           DEFAULT_DIRECTKEYING     = false;
    constexpr uint32_t       DEFAULT_OPAQUELIMIT      = 3;
    constexpr uint8_t        DEFAULT_TRANSPARENTALPHA = 128;
    constexpr const wchar_t* DEFAULT_WEBDICTURL       = L"https://www.google.co.jp/search?q=~A";
    constexpr const int      DEFAULT_SLEEPTIME        = 50;
    //[Style]
    constexpr const int      DEFAULT_BOXCHARCOUNT     = 25;
    constexpr const int      DEFAULT_LISTROWCOUNT     = 10;
    constexpr const int      DEFAULT_WNDOFFSET_X      = 18;
    constexpr const int      DEFAULT_WNDOFFSET_Y      = 18;
    constexpr const wchar_t* DEFAULT_BOXTYPE          = L"sunken";
    constexpr const wchar_t* DEFAULT_CURSORTYPEON     = L"block";
    constexpr const wchar_t* DEFAULT_CURSORTYPEOFF    = L"block";
    constexpr const int      DEFAULT_DISTANCE         = 10;
    constexpr const int      DEFAULT_ROUND_R          = 6;
    constexpr const int      DEFAULT_BEZEL_WIDTH      = 8;
    constexpr const int      DEFAULT_INNER_MARGIN     = 6;
    constexpr const wchar_t* DEFAULT_FONTNAME         = L"\xFF2D\xFF33\x0020\xFF30\x30B4\x30B7\x30C3\x30AF"; // ＭＳ Ｐゴシック
    constexpr uint32_t       DEFAULT_FONTSIZE         = 12;
    constexpr bool           DEFAULT_FONTBOLD         = false;


    //--------------------------------------------------------------------------
    //
    //
    //
    //--------------------------------------------------------------------------
    const wchar_t* FindLastChar( const wchar_t* p1, const wchar_t* p2, wchar_t ch );
    static EngineInfo* CreateEngineInfo( const IniFile& ini );
    static std::string ConvertString( const wchar_t* pTop,
                                      const wchar_t* pEnd = nullptr );
    static bool CheckWinMsgSendMethod( uint32_t& sendMethod,
                                       const wchar_t* p1, const wchar_t* p2,
                                       const wchar_t* pTag, uint32_t tagLen, uint32_t msgCode );
    static bool LoadSendMethod( uint32_t& sendMethod, const wchar_t* p1, const wchar_t* p2 );
    static uint32_t LoadMultiEntries( const IniFile& ini,
                                      const wchar_t* pGroup,
                                      const wchar_t* pEntry,
                                      void(*pCallback)(const wchar_t*,
                                                       const wchar_t*,void*),
                                      void* pOpaque );
    template <typename C>
    void LoadPasteCommands( const wchar_t* p1,
                            const wchar_t* pEnd, void* pOpaque ) {
        auto p2 = std::find( p1, pEnd, ':' );
        if( p2 == pEnd )
            return;
        std::wstring title{ p1, p2++ };
        uint32_t sendMethod = 0;
        if( LoadSendMethod( sendMethod, p2, pEnd ) == false )
            return;
        auto pContainer = reinterpret_cast<C*>( pOpaque );
        pContainer->emplace_back( title, sendMethod );
    }

    //--------------------------------------------------------------------------
    //
    // implementation of class Config
    //
    //--------------------------------------------------------------------------
    Config::Config( const wchar_t* pFileName ) : m_pEngineInfo( nullptr ) {

        IniFile ini( pFileName );
        const wchar_t* sec = nullptr;

        //[Engine]
        m_pEngineInfo = CreateEngineInfo( ini );

        //[SendMethod]
        sec = L"SendMethod"; {
            LoadMultiEntries( ini, sec, L"Method",
                              LoadPasteCommands<SendMethodEntries>, &m_sendMethods );
            const wchar_t* pDefault = ini.Read( sec, L"Default", DEFAULT_SENDMETHOD );
            uint32_t tmp = 0;
            if( LoadSendMethod( tmp, pDefault, pDefault + ::wcslen( pDefault ) ) )
                m_defaultSendMethod = tmp;
        }
        //[Behavior]
        sec = L"Behavior";
        auto kbd = ini.ReadNumeric<int>( sec, L"Keyboard", DEFAULT_KBDTYPE );
        switch( kbd ) {
        case 101:  m_kbdType = KbdType::KB_101; break;
        case 106:  m_kbdType = KbdType::KB_106; break;
        default:   m_kbdType = KbdType::KB_106; break;
        }
        m_emacsKeyBind     = ini.ReadBool( sec, L"EmacsKeyBind", DEFAULT_EMACSKEYBIND );
        m_fwdEmacsKey      = ini.ReadBool( sec, L"ForwardEmacsKey", DEFAULT_FWDEMACSKEY );
        m_predictAfterFix  = ini.ReadBool( sec, L"PredictAfterFix", DEFAULT_PREDICTAFTERFIX );
        m_indexing         = ini.ReadBool( sec, L"Indexing", DEFAULT_INDEXING );
        m_directKey        = ini.ReadBool( sec, L"DirectKey", DEFAULT_DIRECTKEYING );
        m_opaqueLimit      = ini.ReadNumeric<uint32_t>( sec, L"OpaqueLimit", DEFAULT_OPAQUELIMIT );
        m_transparentAlpha = ini.ReadNumeric<uint8_t>( sec, L"TransparentAlpha", DEFAULT_TRANSPARENTALPHA );
        m_webDictURL       = ini.Read( sec, L"WebDictURL", DEFAULT_WEBDICTURL );
        m_sleepTime        = ini.ReadNumeric<int>( sec, L"SleepTime", DEFAULT_SLEEPTIME );

        //[DirectKey]
        sec = L"DirectKey";
        LoadDirectKeys( ini, sec );

        //[Style]
        sec = L"Style";
        m_boxCharCount = ini.ReadNumeric<int>( sec, L"BoxCharCount", DEFAULT_BOXCHARCOUNT );
        m_listRowCount = ini.ReadNumeric<int>( sec, L"ListRowCount", DEFAULT_LISTROWCOUNT );
        m_wndOffsetX = ini.ReadNumeric<int>( sec, L"WndOffsetX", DEFAULT_WNDOFFSET_X ) * -1;
        m_wndOffsetY = ini.ReadNumeric<int>( sec, L"WndOffsetY", DEFAULT_WNDOFFSET_Y );
        auto border = ini.Read( sec, L"BoxType", DEFAULT_BOXTYPE );
        if( !::wcscmp( border, L"flat" ) )
            m_boxType = BoxType::FLAT;
        else if( !::wcscmp( border, L"sunken" ) )
            m_boxType = BoxType::SUNKEN;
        else if( !::wcscmp( border, L"raised" ) )
            m_boxType = BoxType::RAISED;
        else if( !::wcscmp( border, L"etched" ) )
            m_boxType = BoxType::ETCHED;
        else
            m_boxType = BoxType::FLAT;
        m_cursorTypeOn  = LoadCursorType( ini, sec, L"CursorOn", DEFAULT_CURSORTYPEON );
        m_cursorTypeOff = LoadCursorType( ini, sec, L"CursorOff", DEFAULT_CURSORTYPEOFF );
        m_distance      = ini.ReadNumeric<int>( sec, L"Distance", DEFAULT_DISTANCE );
        m_wndRoundR     = ini.ReadNumeric<int>( sec, L"RoundR", DEFAULT_ROUND_R );
        m_bezelWidth    = ini.ReadNumeric<int>( sec, L"BezelWidth", DEFAULT_BEZEL_WIDTH );
        m_innerMargin   = ini.ReadNumeric<int>( sec, L"InnerMargin", DEFAULT_INNER_MARGIN );
        m_fontName      = ini.Read( sec, L"FontName", DEFAULT_FONTNAME );
        m_fontSize      = ini.ReadNumeric<uint32_t>( sec, L"FontSize", DEFAULT_FONTSIZE );
        m_fontBold      = ini.ReadBool( sec, L"FontBold", DEFAULT_FONTBOLD );

        //[Color]
        auto pDefaultTheme = new ColorTheme{ ini, L"Color" };
        m_clrThemes.push_back( pDefaultTheme );
        m_curTheme = 0;

        //[SubThemes]
        sec = L"SubThemes";
        auto pair = std::make_pair( &ini, &m_clrThemes );
        auto callback = []( const wchar_t* p1,
                            const wchar_t* p2, void* pOpaque ) -> void {
            auto pPair = reinterpret_cast<std::pair<IniFile*,ColorThemes*>*>( pOpaque );
            if( !(p1 < p2) )
                return;
            std::wstring section{ p1, p2 };    //MEMO : need this...
            IniFile&     iniFile   = *(pPair->first);
            ColorThemes& clrThemes = *(pPair->second);
            auto pNewTheme = new ColorTheme{ iniFile, section.c_str() };
            clrThemes.push_back( pNewTheme );
        };
        LoadMultiEntries( ini, sec, L"Section", callback, &pair );
    }

    Config::~Config() {
        if( !!m_pEngineInfo ) {
            delete m_pEngineInfo;
            m_pEngineInfo = nullptr;
        }
        for( unsigned int i = 0; i < countof(m_directKeyMap); ++i ) {
            wchar_t*& p = m_directKeyMap[i];
            if( !!p ) {
                delete[] p;
                p = nullptr;
            }
        }
        for( ColorTheme*& pTheme : m_clrThemes ) {
            delete pTheme;
            pTheme = nullptr;
        }
    }

    const RECT& Config::GetTextBoxRect( RECT& rct,
                                        const RECT& client, bool bBelow ) const {
        rct.left = m_bezelWidth;
        rct.top = (m_distance * bBelow) + m_bezelWidth;
        rct.right = client.right - m_bezelWidth - 2;
        rct.bottom = rct.top + (m_fontSize + 4);
        return rct;
    }

    const RECT& Config::GetListBoxRect( RECT& rct,
                                        const RECT& client, bool bBelow ) const {
        rct.left = m_bezelWidth;
        rct.top = (m_distance * bBelow) + m_bezelWidth +
            (m_fontSize + 4) + m_innerMargin;
        rct.right = client.right - m_bezelWidth - 2;
        rct.bottom = client.bottom - (m_distance * !bBelow) - m_bezelWidth - 2;
        return rct;
    }

    void Config::GetSendMethod( const wchar_t* pWndTitle, uint32_t& sendMethod ) const {
        for( const auto& entry : m_sendMethods ) {
            const std::wstring& title = entry.first;
            if( !::wcsncmp( title.c_str(), pWndTitle, title.size() ) ) {
                sendMethod = entry.second;
                return;
            }
        }
        sendMethod = m_defaultSendMethod;
    }

    bool Config::GetDirectKey( int keyCode, wchar_t* pBuf ) const {
        if( m_directKeyMap[keyCode] == nullptr )
            return false;
        ::wcscpy( pBuf, m_directKeyMap[keyCode] );
        return true;
    }

    CursorType Config::LoadCursorType( IniFile& ini, const wchar_t* pSection,
                                       const wchar_t* pKey, const wchar_t* pDefaultValue ) {
        auto cursor = ini.Read( pSection, pKey, pDefaultValue );
        if( !::wcscmp( cursor, L"block" ) )
            return CursorType::BLOCK;
        else if( !::wcscmp( cursor, L"line" ) )
            return  CursorType::LINE;
        else if( !::wcscmp( cursor, L"underscore" ) )
            return  CursorType::UNDERSCORE;
        else
            return  CursorType::BLOCK;
    }

    void Config::LoadDirectKeys( IniFile& ini, const wchar_t* pSection ) {
        std::fill( m_directKeyMap,
                   m_directKeyMap + countof(m_directKeyMap), nullptr );
        LoadMultiEntries( ini, pSection, L"Key",
                          []( const wchar_t* pTop,
                              const wchar_t* pEnd, void* pOpaque ) -> void {
                              auto len = pEnd - pTop;
                              if( 2 <= len ) {
                                  int key = *pTop;
                                  wchar_t* pBuf = new wchar_t[len];
                                  ::wcscpy( pBuf, pTop + 1 );
                                  reinterpret_cast<wchar_t**>( pOpaque )[key] = (wchar_t*)pBuf;
                              }
                          }, &m_directKeyMap );
    }


    //--------------------------------------------------------------------------
    //
    // local functions
    //
    //--------------------------------------------------------------------------
    const wchar_t* FindLastChar( const wchar_t* p1, const wchar_t* p2, wchar_t ch ) {
        const wchar_t* p = 0;
        for( ; p1 < p2; ++p1 ) {
            if( *p1 == ch )
                p = p1;
        }
        return p ? p : p2;
    }

    static EngineInfo* CreateEngineInfo( const IniFile& ini ) {
        // create remote engine.
        std::string srvName = ConvertString( ini.Read( L"Engine", L"Host", DEFAULT_SERVERNAME ) );
        uint32_t    srvPort = ini.ReadNumeric<uint32_t>( L"Engine", L"Port", DEFAULT_SERVERPORT );
        uint32_t    candMax  = ini.ReadNumeric<uint32_t>( L"Engine", L"CandMax", DEFAULT_CANDMAX );
        return new EngineInfo{ srvName, srvPort, candMax };
    }

    static std::string ConvertString( const wchar_t* pTop, const wchar_t* pEnd ) {
        if( !pEnd )
            pEnd = pTop + ::wcslen( pTop );
        char buf[1024];
        int byteLen = WinAPI::WideCharToMultiByte( CP_UTF8, 0, //WC_ERR_INVALID_CHARS,
                                                   pTop, pEnd - pTop, buf, 1024, NULL, NULL );
        (void)byteLen;
        return std::string{ buf, buf + byteLen };
    }

    static bool CheckWinMsgSendMethod( uint32_t& sendMethod,
                                       const wchar_t* p1, const wchar_t* p2,
                                       const wchar_t* pTag, uint32_t tagLen, uint32_t msgCode ) {
        uint32_t len = p2 - p1;
        if( len < tagLen )
            return false;
        if( ::wcsncmp( p1, pTag, tagLen ) != 0 )
            return false;
        uint32_t msecInterval = 0;
        if( tagLen < len ) {
            if( p1[tagLen] != L'/' )
                return false;
            for( const wchar_t* p = p1 + tagLen + 1; p < p2; ++p ) {
                if( !( L'0' <= *p && *p <= L'9' ) )
                    return false;
                msecInterval = (msecInterval * 10) + (*p - L'0');
            }
        }
        sendMethod = SendMethod::MakeWinMesasge( msgCode, msecInterval );
        return true;
    }

    static bool LoadSendMethod( uint32_t& sendMethod, const wchar_t* p1, const wchar_t* p2 ) {
        if( CheckWinMsgSendMethod( sendMethod, p1, p2, L"WM_CHAR", 7, WM_CHAR ) )
            return true;
        if( CheckWinMsgSendMethod( sendMethod, p1, p2, L"WM_UNICHAR", 10, WM_UNICHAR ) )
            return true;
        int32_t bucky1 = 0;
        int32_t bucky2 = 0;
        int32_t key    = 0;
        auto p3 = FindLastChar( p1, p2, '+' );
        if( p3 == p2 )
            return false;
        switch( p3++ - p1 ) {
        case  3: if( !::wcsncmp( p1, L"Alt",         3 ) )   bucky1 = VK_MENU;     break;
        case  4: if( !::wcsncmp( p1, L"Ctrl",        4 ) )   bucky1 = VK_CONTROL;  break;
        case  5: if( !::wcsncmp( p1, L"Shift",       5 ) )   bucky1 = VK_SHIFT;    break;
        case  8: if( !::wcsncmp( p1, L"Ctrl+Alt",    8 ) ) { bucky1 = VK_CONTROL;
                bucky2 = VK_MENU;   } break;
        case 10: if( !::wcsncmp( p1, L"Ctrl+Shift", 10 ) ) { bucky1 = VK_CONTROL;
                bucky2 = VK_SHIFT;  } break;
        }
        if( bucky1 == 0 )
            return false;
        switch( p2 - p3 ) {
        case 1:                                     key = *p3;        break;
        case 3: if( !::wcsncmp( p3, L"Ins",   3 ) ) key = VK_INSERT;  break;
        }
        if( key == 0 )
            return false;
        sendMethod = SendMethod::MakePasteKey( bucky1, bucky2, key );
        return true;
    }

    static uint32_t LoadMultiEntries( const IniFile& ini,
                                      const wchar_t* pGroup,
                                      const wchar_t* pEntry,
                                      void(*pCallback)(const wchar_t*,const wchar_t*,void*),
                                      void* pOpaque ) {
        uint32_t count = 0;
        wchar_t fmt[64];
        wchar_t buf[64];
        ::wsprintfW( fmt, L"%s%%02u", pEntry );
        for( uint32_t idx = 1; idx < 100; ++idx ) {
            ::wsprintfW( buf, fmt, idx );
            const wchar_t* p1 = ini.Read( pGroup, buf, L"" );
            if( !p1 || !*p1 )
                break;
            pCallback( p1, p1 + ::wcslen( p1 ), pOpaque );
            ++count;
        }
        return count;
    }

} // namespace clime

