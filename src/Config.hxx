//------------------------------------------------------------------------------
//
// Config.hxx
//
//------------------------------------------------------------------------------
#ifndef CONFIG_HXX__
#define CONFIG_HXX__

#include "Common.hxx"

#include "WinAPI.hxx"

#include "DictionaryInfo.hxx"
#include "SendMethod.hxx"

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>


namespace clime {

    class IniFile;
    class EngineInfo;
    class ColorTheme;

    class Config {
    private:
        using SendMethodEntry = std::pair<std::wstring,uint32_t>;
        using SendMethodEntries = std::vector<SendMethodEntry>;
        using ColorThemes = std::vector<ColorTheme*>;
    public:
        Config() = delete;
        Config( const wchar_t* pFileName );
        Config( const Config& ) = delete;
        ~Config();
        Config& operator=( const Config& ) = delete;
    public:
        //[Engine]
        inline const EngineInfo& GetEngineInfo() const { return *m_pEngineInfo; }
        //[Behavior]
        inline KbdType KeyboardType() const { return m_kbdType; }
        inline bool EmacsKeyBind() const { return m_emacsKeyBind; }
        inline bool ForwardEmacsKey() const { return m_fwdEmacsKey; }
        inline bool PredictAfterFix() const { return m_predictAfterFix; }
        inline bool Indexing() const { return m_indexing; }
        inline bool DirectKey() const { return m_directKey; }
        inline uint32_t OpaqueLimit() const { return m_opaqueLimit; }
        inline uint8_t TransparentAlpha() const { return m_transparentAlpha; }
        inline int SleepTime() const { return m_sleepTime; }
        inline std::wstring WebDictURL() const { return m_webDictURL; }
        //[Style]
        inline int GetBoxCharCount() const { return m_boxCharCount; }
        inline int GetListRowCount() const { return m_listRowCount; }
        inline int GetWndOffsetX() const { return m_wndOffsetX; }
        inline int GetWndOffsetY() const { return m_wndOffsetY; }
        inline BoxType GetBoxType() const { return m_boxType; }
        inline CursorType GetCursorType( bool bConverting ) const {
            return ( bConverting ? m_cursorTypeOn : m_cursorTypeOff );
        }
        inline int GetDistance() const { return m_distance; }
        inline int GetWndRoundR() const { return m_wndRoundR; }
        inline int GetBezelWidth() const { return m_bezelWidth; }
        inline int GetInnerMargin() const { return m_innerMargin; }
        inline std::wstring FontName() const { return m_fontName; }
        inline uint32_t FontSize() const { return m_fontSize; }
        inline bool FontBold() const { return m_fontBold; }
        //[Color]
        inline const ColorTheme& GetTheme() const { return *(m_clrThemes[m_curTheme]); }
        inline void NextTheme() const {
            if( ++m_curTheme == m_clrThemes.size() )
                m_curTheme = 0;
        }
    public:
        const RECT& GetTextBoxRect( RECT& rct, const RECT& client, bool bBelow ) const;
        const RECT& GetListBoxRect( RECT& rct, const RECT& client, bool bBelow ) const;
        void GetSendMethod( const wchar_t* pWndTitle, uint32_t& sendMethod ) const;
        bool GetDirectKey( int keyCode, wchar_t* pBuf ) const;
    private:
        CursorType LoadCursorType( IniFile& iniFile, const wchar_t* pSection,
                                   const wchar_t* pKey, const wchar_t* pDefaultValue );
        void LoadDirectKeys( IniFile& iniFile, const wchar_t* pSection );
    private:
        //[Engine]
        EngineInfo*         m_pEngineInfo;
        //[SendMethod]
        uint32_t            m_defaultSendMethod;
        SendMethodEntries   m_sendMethods;
        //[Behavior]
        KbdType             m_kbdType;
        bool                m_emacsKeyBind;
        bool                m_fwdEmacsKey;
        bool                m_predictAfterFix;
        bool                m_indexing;
        bool                m_directKey;
        int                 m_sleepTime;
        uint32_t            m_opaqueLimit;
        uint8_t             m_transparentAlpha;
        std::wstring        m_webDictURL;
        //[DirectKey]
        wchar_t*            m_directKeyMap[128];
        //[Style]
        uint32_t            m_boxCharCount;
        uint32_t            m_listRowCount;
        int                 m_wndOffsetX;
        int                 m_wndOffsetY;
        BoxType             m_boxType;
        CursorType          m_cursorTypeOn;
        CursorType          m_cursorTypeOff;
        int                 m_distance;
        int                 m_wndRoundR;
        int                 m_bezelWidth;
        int                 m_innerMargin;
        std::wstring        m_fontName;
        uint32_t            m_fontSize;
        bool                m_fontBold;
        //[Color]
        mutable uint32_t    m_curTheme;
        ColorThemes         m_clrThemes;
    };

} // namespace clime

#endif // CONFIG_HXX__
