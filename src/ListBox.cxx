//------------------------------------------------------------------------------
//
// ListBox.cxx
//
//------------------------------------------------------------------------------
#include "ListBox.hxx"
#include "Box.hxx"
#include "Config.hxx"
#include "ColorTheme.hxx"
#include "Candidates.hxx"

namespace clime {

    ListBox::ListBox( const Config& cfg ) : Box( cfg ),
                                            m_indexWidth( 0 ) {
    }

    ListBox::~ListBox() {
        //intentionally do nothing...
    }

    void ListBox::DrawListBox( HDC hdc, const Config& cfg, bool bIndexing,
                               int xOffset, const Candidates& cands, const RECT& rect ) {

        auto& theme = cfg.GetTheme();

        if( bIndexing && !m_indexWidth ) {
            SIZE size;
            WinAPI::GetTextExtentPoint32( hdc, L"1 ", 2, &size );
            m_indexWidth = size.cx;
        }

        uint32_t idxWidth = ( bIndexing ? m_indexWidth : 0 );

        auto clrCand  = theme.clrCandidate;
        auto clrIndex = theme.clrIndex;

        if( idxWidth < (uint32_t)xOffset - cfg.GetBezelWidth() )
            xOffset -= idxWidth;

        void* pOpaque = nullptr;
        RECT rect2;
        if( bIndexing == false )
            WinAPI::SetTextColor( hdc, clrCand );
        else if( cands.Empty() == false ) {
            rect2 = rect;
            rect2.right = xOffset + idxWidth - 2;
            rect2.left  = xOffset -4;
            if( rect2.left < rect.left )
                rect2.left = rect.left;
            pOpaque = &rect2;
        }

        DrawBox( theme, hdc, rect, pOpaque );

        //■候補の残りの一覧を表示
        wchar_t index[3] = { L'1', L' ', 0 };
        const int rowMax = (rect.bottom - rect.top) / cfg.FontSize();
        uint32_t sel = cands.Selection();
        for( int i = 0; sel+i < cands.Size() && i < rowMax && i < 20; ++i ) {
            if( bIndexing && 0 <= i && i < 9 ) {
                WinAPI::SetTextColor( hdc, clrIndex );
                index[0] = L'1' + i;
                WinAPI::TextOut( hdc, xOffset, rect.top + 3 + i * cfg.FontSize(), index, 2 );
                WinAPI::SetTextColor( hdc, clrCand );
            }
            const wchar_t*  pData = cands[sel+i];
            int             cnt   = cands.LengthOf( sel+i );
            WinAPI::TextOut( hdc, xOffset + idxWidth,
                             rect.top + 3 + i * cfg.FontSize(), pData, cnt );
        }
    }

    void ListBox::AfterFill( const ColorTheme& theme, HDC hdc,
                             const RECT& /*rect*/, void* pOpaque ) {
        if( !!pOpaque ) {
            RECT* pRect = reinterpret_cast<RECT*>( pOpaque );
            WinAPI::FillRect( hdc, pRect, theme.brshIndexBG );
        }
    }

} // namespace clime

