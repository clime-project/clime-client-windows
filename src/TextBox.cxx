//------------------------------------------------------------------------------
//
// TextBox.cxx
//
//------------------------------------------------------------------------------
#include "TextBox.hxx"

#include "Config.hxx"
#include "ColorTheme.hxx"
#include "UTF16.hxx"

#include <algorithm>

namespace clime {

    static bool IsParenPair( const wchar_t* pUnicodeText, int len );

    //--------------------------------------------------------------------------
    //
    // implementation of TextBox
    //
    //--------------------------------------------------------------------------
    TextBox::TextBox( const Config& cfg ) : Box( cfg ) {
    }

    TextBox::~TextBox() {
        //intentionally do nothing...
    }

    void TextBox::Clear() {
        m_text.clear();
        m_caretPos = 0;
    }

    void TextBox::Insert( const wchar_t* pUnicodeText ) {
        auto cnt = ::wcslen( pUnicodeText );
        m_text.insert( m_text.begin() + m_caretPos,
                       pUnicodeText, pUnicodeText + cnt );
        m_caretPos += cnt;
        if( IsParenPair( pUnicodeText, cnt ) )
            --m_caretPos;
    }

    void TextBox::DeleteCaretChar() {
        if( m_text.empty() || m_caretPos == m_text.length() )
            return;
        uint32_t nextPos = GetNextPos();
        m_text.erase( m_text.begin() + m_caretPos, m_text.begin() + nextPos );
    }

    void TextBox::OperateBackspace() {
        if( !m_caretPos || m_text.empty() )
            return;
        uint32_t prevPos = GetPrevPos();
        m_text.erase( m_text.begin() + prevPos, m_text.begin() + m_caretPos );
        m_caretPos = prevPos;
    }

    void TextBox::OperateCtrlT() {
        if( !m_caretPos || m_text.empty() )
            return;
        if( m_caretPos == m_text.length() )
            m_caretPos = GetPrevPos();
        auto prev = GetPrevPos();
        auto next = GetNextPos();
        auto itr = m_text.begin();
        std::rotate( itr + prev, itr + m_caretPos, itr + next );
        m_caretPos = next;
    }

    void TextBox::ChompAfterCaret() {
        if( m_text.empty() || m_caretPos == m_text.length() )
            return;
        m_text.erase( m_text.begin() + m_caretPos, m_text.end() );
    }

    int TextBox::DrawTextBox( HDC hdc, const Config& cfg, bool bConverting,
                              const wchar_t* pSelText, int selTextLen, const RECT& rect ) {

        auto& theme = cfg.GetTheme();
        DrawBox( theme, hdc, rect );

        const wchar_t* pText = m_text.c_str();
        int x = cfg.GetBezelWidth() + 3;
        int y = rect.top + 3;

        //■変換済みのテキスト（カーソル手前まで）を表示
        SIZE size;
        WinAPI::SetBkColor(   hdc, theme.clrBackGround );
        WinAPI::SetTextColor( hdc, theme.clrTexts );
        WinAPI::TextOut( hdc, x, y, pText, m_caretPos );
        WinAPI::GetTextExtentPoint32( hdc, pText, m_caretPos, &size );
        x += size.cx;

        const int ret = x;

        //■選択中の変換候補テキストを表示
        WinAPI::SetTextColor( hdc, theme.clrSelection );
        WinAPI::TextOut( hdc, x, y, pSelText, selTextLen );
        WinAPI::GetTextExtentPoint32( hdc, pSelText, selTextLen, &size );
        x += size.cx;

        //■カーソル（のようなモノ）を描画
        {
            const int fSize    = cfg.FontSize();
            const int chrWidth = ((0xFF < pText[m_caretPos]) ? fSize : fSize/2);
            RECT tmp;
            switch( cfg.GetCursorType( bConverting ) ) {
            case CursorType::BLOCK:
                WinAPI::SetRect( &tmp, x, y, x + chrWidth, y + fSize );
                break;
            case CursorType::LINE:
                WinAPI::SetRect( &tmp, x, y, x + 2, y + fSize );
                break;
            case CursorType::UNDERSCORE:
                WinAPI::SetRect( &tmp, x, y + fSize - 1, x + chrWidth, y + fSize + 1 );
                break;
            }
            WinAPI::FillRect( hdc, &tmp,
                              (bConverting ? theme.brshCursorOn : theme.brshCursorOff) );
        }

        //■変換済みのテキスト（カーソル以降）を表示
        WinAPI::SetTextColor( hdc, theme.clrTexts );
        const wchar_t* p = pText + m_caretPos;
        auto len = m_text.length() - m_caretPos;
        WinAPI::TextOut( hdc, x, y, p, len );
        WinAPI::GetTextExtentPoint32( hdc, p, len, &size );
        x += size.cx;

        return ret;
    }

    uint32_t TextBox::GetNextPos() const {
        uint32_t pos = m_caretPos;
        if( m_caretPos < m_text.length() ) {
            const wchar_t* pTop = &(m_text[0]);
            const wchar_t* pCur = pTop + m_caretPos;
            pos = UTF16::Increment( pCur ) - pTop;
        }
        return pos;
    }

    uint32_t TextBox::GetPrevPos() const {
        uint32_t pos = m_caretPos;
        if( 0 < m_caretPos ) {
            const wchar_t* pTop = &(m_text[0]);
            const wchar_t* pCur = pTop + m_caretPos;
            pos = UTF16::Decrement( pTop, pCur ) - pTop;
        }
        return pos;
    }

    //--------------------------------------------------------------------------
    //
    // local functions
    //
    //--------------------------------------------------------------------------
    static bool IsParenPair( const wchar_t* pUnicodeText, int len ) {
        if( len != 2 )
            return false;
        if( pUnicodeText[0] == 0x300C && pUnicodeText[1] == 0x300D ) return true; // 「」
        if( pUnicodeText[0] == 0x300E && pUnicodeText[1] == 0x300F ) return true; // 『』
        if( pUnicodeText[0] == 0x3008 && pUnicodeText[1] == 0x3009 ) return true; // 〈〉
        if( pUnicodeText[0] == 0x3010 && pUnicodeText[1] == 0x3011 ) return true; // 【】
        if( pUnicodeText[0] == 0x300A && pUnicodeText[1] == 0x300B ) return true; // 《》
        if( pUnicodeText[0] == 0x3014 && pUnicodeText[1] == 0x3015 ) return true; // 〔〕
        if( pUnicodeText[0] == 0xFF1C && pUnicodeText[1] == 0xFF1E ) return true; // ＜＞
        if( pUnicodeText[0] == 0xFF08 && pUnicodeText[1] == 0xFF09 ) return true; // （）
        if( pUnicodeText[0] == 0xFF3B && pUnicodeText[1] == 0xFF3D ) return true; // ［］
        if( pUnicodeText[0] == 0xFF5B && pUnicodeText[1] == 0xFF5D ) return true; // ｛｝
        if( pUnicodeText[0] == 0x2018 && pUnicodeText[1] == 0x2019 ) return true; // ‘’
        if( pUnicodeText[0] == 0x201C && pUnicodeText[1] == 0x201D ) return true; // “”
        return false;
    }


} // namespace clime

