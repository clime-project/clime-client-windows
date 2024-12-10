//------------------------------------------------------------------------------
//
// Box.cxx
//
//------------------------------------------------------------------------------
#include "Box.hxx"

#include "Config.hxx"
#include "ColorTheme.hxx"

namespace clime {

    //--------------------------------------------------------------------------
    //
    // implementation of class Box
    //
    //--------------------------------------------------------------------------
    Box::Box( const Config& cfg ) {
        switch( cfg.GetBoxType() ) {
        case BoxType::FLAT:     m_pHandler = &clime::Box::DrawImpForFlat;    break;
        case BoxType::SUNKEN:   m_pHandler = &clime::Box::DrawImpForSunken;  break;
        case BoxType::RAISED:   m_pHandler = &clime::Box::DrawImpForRaised;  break;
        case BoxType::ETCHED:   m_pHandler = &clime::Box::DrawImpForEtched;  break;
        default:                m_pHandler = &clime::Box::DrawImpForFlat;    break;
        }
    }

    Box::~Box() {
    }

    void Box::DrawLine( HDC hdc, int x1, int y1, int x2, int y2, HPEN pen ) {
        POINT p[2];
        WinAPI::SelectObject( hdc, pen );
        p[0].x = x1; p[0].y = y1;
        p[1].x = x2; p[1].y = y2;
        WinAPI::Polyline( hdc, p, 2 );
    }

    void Box::DrawImpForFlat( const ColorTheme& theme,
                              HDC hdc, const RECT& rect, void* pOpaque ) {
        // テキストボックスもどきの描画
        WinAPI::FillRect( hdc, &rect, theme.brshBackGround );
        this->AfterFill( theme, hdc, rect, pOpaque );
        const auto& x1 = rect.left;
        const auto& y1 = rect.top;
        const auto& x2 = rect.right;
        const auto& y2 = rect.bottom;
        DrawLine( hdc, x1, y1, x2, y1, theme.penBoxBorder3 );
        DrawLine( hdc, x1, y2, x2, y2, theme.penBoxBorder3 );
        DrawLine( hdc, x1, y1, x1, y2, theme.penBoxBorder3 );
        DrawLine( hdc, x2, y1, x2, y2, theme.penBoxBorder3 );
    }

    void Box::DrawImpForSunken( const ColorTheme& theme,
                                HDC hdc, const RECT& rect, void* pOpaque ) {
        // テキストボックスもどきの描画
        WinAPI::FillRect( hdc, &rect, theme.brshBackGround );
        this->AfterFill( theme, hdc, rect, pOpaque );
        const auto& x1 = rect.left;
        const auto& y1 = rect.top;
        const auto& x2 = rect.right;
        const auto& y2 = rect.bottom;
        DrawLine( hdc, x1,   y1,   x1,     y2-1+1, theme.penBoxBorder4 );
        DrawLine( hdc, x1,   y1,   x2-1+1, y1,     theme.penBoxBorder4 );
        DrawLine( hdc, x1,   y2,   x2+1,   y2,     theme.penBoxBorder2 );
        DrawLine( hdc, x2,   y1,   x2,     y2+1,   theme.penBoxBorder2 );
        DrawLine( hdc, x1-1, y1-1, x1-1,   y2+1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y1-1, x2+1,   y1-1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y2+1, x2+1+1, y2+1,   theme.penBoxBorder1 );
        DrawLine( hdc, x2+1, y1-1, x2+1,   y2+1+1, theme.penBoxBorder1 );
    }

    void Box::DrawImpForRaised( const ColorTheme& theme,
                                HDC hdc, const RECT& rect, void* pOpaque ) {
        // テキストボックスもどきの描画
        WinAPI::FillRect( hdc, &rect, theme.brshBackGround );
        this->AfterFill( theme, hdc, rect, pOpaque );
        const auto& x1 = rect.left;
        const auto& y1 = rect.top;
        const auto& x2 = rect.right;
        const auto& y2 = rect.bottom;
        DrawLine( hdc, x1,   y1,   x1,     y2-1+1, theme.penBoxBorder1 );
        DrawLine( hdc, x1,   y1,   x2-1+1, y1,     theme.penBoxBorder1 );
        DrawLine( hdc, x1,   y2,   x2+1,   y2,     theme.penBoxBorder3 );
        DrawLine( hdc, x2,   y1,   x2,     y2+1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y1-1, x1-1,   y2+1,   theme.penBoxBorder2 );
        DrawLine( hdc, x1-1, y1-1, x2+1,   y1-1,   theme.penBoxBorder2 );
        DrawLine( hdc, x1-1, y2+1, x2+1+1, y2+1,   theme.penBoxBorder4 );
        DrawLine( hdc, x2+1, y1-1, x2+1,   y2+1+1, theme.penBoxBorder4 );
    }

    void Box::DrawImpForEtched( const ColorTheme& theme,
                                HDC hdc, const RECT& rect, void* pOpaque ) {
        // テキストボックスもどきの描画
        WinAPI::FillRect( hdc, &rect, theme.brshBackGround );
        this->AfterFill( theme, hdc, rect, pOpaque );
        const auto& x1 = rect.left;
        const auto& y1 = rect.top;
        const auto& x2 = rect.right;
        const auto& y2 = rect.bottom;
        DrawLine( hdc, x1,   y1,   x1,     y2-1+1, theme.penBoxBorder1 );
        DrawLine( hdc, x1,   y1,   x2-1+1, y1,     theme.penBoxBorder1 );
        DrawLine( hdc, x1,   y2,   x2+1,   y2,     theme.penBoxBorder3 );
        DrawLine( hdc, x2,   y1,   x2,     y2+1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y1-1, x1-1,   y2+1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y1-1, x2+1,   y1-1,   theme.penBoxBorder3 );
        DrawLine( hdc, x1-1, y2+1, x2+1+1, y2+1,   theme.penBoxBorder1 );
        DrawLine( hdc, x2+1, y1-1, x2+1,   y2+1+1, theme.penBoxBorder1 );
    }

} // namespace clime

