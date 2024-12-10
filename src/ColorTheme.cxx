//------------------------------------------------------------------------------
//
// ColorTheme.cxx
//
//------------------------------------------------------------------------------
#include "ColorTheme.hxx"

#include "IniFile.hxx"
#include "Colors.hxx"

namespace clime {

    //[Color]
    constexpr const wchar_t*  DEFAULT_BEZELCOLOR        = L"FF:E0:70";
    constexpr const wchar_t*  DEFAULT_BACKGROUNDCOLOR   = L"white";
    constexpr const wchar_t*  DEFAULT_BOXBORDER1COLOR   = L"white";
    constexpr const wchar_t*  DEFAULT_BOXBORDER2COLOR   = L"E3:E3:E3";
    constexpr const wchar_t*  DEFAULT_BOXBORDER3COLOR   = L"A0:A0:A0";
    constexpr const wchar_t*  DEFAULT_BOXBORDER4COLOR   = L"69:69:69";
    constexpr const wchar_t*  DEFAULT_CURSORCOLOR_ON    = L"69:69:69";
    constexpr const wchar_t*  DEFAULT_CURSORCOLOR_OFF   = L"C0:C0:C0";
    constexpr const wchar_t*  DEFAULT_TEXTSCOLOR        = L"black";
    constexpr const wchar_t*  DEFAULT_SELECTIONCOLOR    = L"blue";
    constexpr const wchar_t*  DEFAULT_CANDSCOLOR        = L"black";
    constexpr const wchar_t*  DEFAULT_INDEXCOLOR        = L"69:69:69";

    //--------------------------------------------------------------------------
    //
    // implementation of class ColorTheme
    //
    //--------------------------------------------------------------------------
    ColorTheme::ColorTheme( IniFile& ini, const wchar_t* sec ) {

        //[Color]
        brshBezel       = LoadBrush( ini, sec, L"Bezel",             DEFAULT_BEZELCOLOR );
        clrBackGround   = LoadColor( ini, sec, L"BackGround",        DEFAULT_BACKGROUNDCOLOR );
        brshBackGround  = WinAPI::CreateSolidBrush( clrBackGround );
        penBoxBorder1   = LoadPen(   ini, sec, L"BoxBorder1",        DEFAULT_BOXBORDER1COLOR );
        penBoxBorder2   = LoadPen(   ini, sec, L"BoxBorder2",        DEFAULT_BOXBORDER2COLOR );
        penBoxBorder3   = LoadPen(   ini, sec, L"BoxBorder3",        DEFAULT_BOXBORDER3COLOR );
        penBoxBorder4   = LoadPen(   ini, sec, L"BoxBorder4",        DEFAULT_BOXBORDER4COLOR );
        brshCursorOn    = LoadBrush( ini, sec, L"CursorOn",          DEFAULT_CURSORCOLOR_ON );
        brshCursorOff   = LoadBrush( ini, sec, L"CursorOff",         DEFAULT_CURSORCOLOR_OFF );
        clrTexts        = LoadColor( ini, sec, L"Texts",             DEFAULT_TEXTSCOLOR );
        clrSelection    = LoadColor( ini, sec, L"Selection",         DEFAULT_SELECTIONCOLOR );
        clrCandidate    = LoadColor( ini, sec, L"Candidate",         DEFAULT_CANDSCOLOR );
        clrIndex        = LoadColor( ini, sec, L"Index",             DEFAULT_INDEXCOLOR );
        brshIndexBG     = LoadBrush( ini, sec, L"IndexBackGround",   brshBackGround );
    }

    ColorTheme::~ColorTheme() {
        //release brushes & pens
        WinAPI::DeleteObject( brshBezel );
        WinAPI::DeleteObject( brshBackGround );
        WinAPI::DeleteObject( penBoxBorder1 );
        WinAPI::DeleteObject( penBoxBorder2 );
        WinAPI::DeleteObject( penBoxBorder3 );
        WinAPI::DeleteObject( penBoxBorder4 );
        WinAPI::DeleteObject( brshCursorOn );
        WinAPI::DeleteObject( brshCursorOff );
        WinAPI::DeleteObject( brshIndexBG );
    }

    int32_t ColorTheme::LoadColor( IniFile& ini, const wchar_t* pSection,
                                   const wchar_t* pKey, const wchar_t* pDefaultValue ) {
        return Colors::Create( ini.Read( pSection, pKey, pDefaultValue ) );
    }

    HPEN ColorTheme::LoadPen( IniFile& ini, const wchar_t* pSection,
                              const wchar_t* pKey, const wchar_t* pDefaultValue ) {
        auto clr = Colors::Create( ini.Read( pSection, pKey, pDefaultValue ) );
        return WinAPI::CreatePen( PS_SOLID, 1, clr );
    }

    HBRUSH ColorTheme::LoadBrush( IniFile& ini, const wchar_t* pSection,
                                  const wchar_t* pKey, const wchar_t* pDefaultValue ) {
        auto clr = Colors::Create( ini.Read( pSection, pKey, pDefaultValue ) );
        return WinAPI::CreateSolidBrush( clr );
    }

    HBRUSH ColorTheme::LoadBrush( IniFile& ini, const wchar_t* pSection,
                                  const wchar_t* pKey, HBRUSH defaultBrush ) {
        auto entry = ini.Read( pSection, pKey, L"" );
        if( !entry || !*entry )
            return defaultBrush;
        else
            return WinAPI::CreateSolidBrush( Colors::Create( entry ) );
    }

} // namespace clime

