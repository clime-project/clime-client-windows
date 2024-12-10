//------------------------------------------------------------------------------
//
// ColorTheme.hxx
//
//------------------------------------------------------------------------------
#ifndef COLORTHEME_HXX__
#define COLORTHEME_HXX__

#include "Common.hxx"
#include "WinAPI.hxx"

#include <stdint.h>

namespace clime {

    class IniFile;

    class ColorTheme {
    public:
        ColorTheme() = delete;
        ColorTheme( IniFile& ini, const wchar_t* sec );
        ColorTheme( const ColorTheme& ) = delete;
        ~ColorTheme();
        ColorTheme& operator=( const ColorTheme& ) = delete;
    private:
        int32_t LoadColor( IniFile& iniFile, const wchar_t* pSection,
                           const wchar_t* pKey, const wchar_t* pDefaultValue );
        HPEN LoadPen( IniFile& iniFile, const wchar_t* pSection,
                      const wchar_t* pKey, const wchar_t* pDefaultValue );
        HBRUSH LoadBrush( IniFile& iniFile, const wchar_t* pSection,
                          const wchar_t* pKey, const wchar_t* pDefaultValue );
        HBRUSH LoadBrush( IniFile& iniFile, const wchar_t* pSection,
                          const wchar_t* pKey, HBRUSH defaultBrush );
    public:
        HBRUSH      brshBezel;
        int32_t     clrBackGround;
        HBRUSH      brshBackGround;
        HPEN        penBoxBorder1;
        HPEN        penBoxBorder2;
        HPEN        penBoxBorder3;
        HPEN        penBoxBorder4;
        HBRUSH      brshCursorOn;
        HBRUSH      brshCursorOff;
        int32_t     clrTexts;
        int32_t     clrSelection;
        int32_t     clrCandidate;
        int32_t     clrIndex;
        HBRUSH      brshIndexBG;
    };

} // namespace clime

#endif // COLORTHEME_HXX__
