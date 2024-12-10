//------------------------------------------------------------------------------
//
// WindowMover.cxx
//
//------------------------------------------------------------------------------
#include "WindowMover.hxx"

#include "Common.hxx"
#include "Config.hxx"

#include <vector>
#include <utility>
#include <algorithm>

namespace clime {

    using MonitorInfo = std::pair<HMONITOR,RECT>;
    using MonitorInfoList = std::vector<MonitorInfo>;

    static MonitorInfoList* g_pMonitors = nullptr;

    class MonitorInfoCleaner {
    public:
        ~MonitorInfoCleaner() {
            if( !!g_pMonitors ) {
                delete g_pMonitors;
                g_pMonitors = nullptr;
            }
        }
    } g_MonitorInfoCleaner;


    //--------------------------------------------------------------------------
    //
    // implementation of class WindowMover
    //
    //--------------------------------------------------------------------------
    WindowMover::WindowMover() : m_curPosition( Position::BELOW ) {
    }

    WindowMover::~WindowMover() {
    }

    void WindowMover::UpdateMonitorInfo() {
        if( !g_pMonitors )
            g_pMonitors = new MonitorInfoList{};
        g_pMonitors->clear();
        WinAPI::EnumDisplayMonitors( 0, 0, MonitorInfoCallback, (LPARAM)g_pMonitors );
    }

    HWND WindowMover::WinSave() {
        m_targetWin = WinAPI::GetForegroundWindow();
        m_targetThread = WinAPI::GetWindowThreadProcessId( m_targetWin, NULL );
        m_selfThread = WinAPI::GetCurrentThreadId();
        WinAPI::AttachThreadInput( m_selfThread, m_targetThread, TRUE );
        m_activeWin = WinAPI::GetFocus();
        m_selection = WinAPI::EditGetSel( m_activeWin );
        return m_activeWin;
    }

    void WindowMover::WinRestore() {
        WinAPI::SetForegroundWindow( m_targetWin );
        WinAPI::SetFocus( m_activeWin );
        WinAPI::EditSetSel( m_activeWin, m_selection );
        WinAPI::AttachThreadInput( m_selfThread, m_targetThread, FALSE );
    }

    bool WindowMover::GetDesktopFromPoint( const POINT& pt, RECT& rect ) const {
        HMONITOR monitor = WinAPI::MonitorFromPoint( pt, 0 );
        auto itr = std::find_if( g_pMonitors->begin(), g_pMonitors->end(),
                                 [&monitor]( const MonitorInfo& info ) {
                                     return info.first == monitor;
                                 } );
        if( itr == g_pMonitors->end() )
            return false;
        rect = itr->second;
        return true;
    }

    WINBOOL CALLBACK WindowMover::MonitorInfoCallback( HMONITOR monitor,
                                                       HDC, LPRECT pRect, LPARAM lparam ) {
        auto pMonitors = reinterpret_cast<MonitorInfoList*>( lparam );
        pMonitors->emplace_back( monitor, *pRect );
        return TRUE;
    }

    void WindowMover::MoveToCursor( HWND hwnd,
                                    const Config& cfg, int width, int height ) {
        POINT pos;
        WinSave();
        // ::GetCaretPos() で取得できない場合は移動しないことにする
        if( WinAPI::GetCaretPos( &pos ) && m_activeWin && pos.x != 0 ) {
            WinAPI::ClientToScreen( m_activeWin, &pos );
            auto left   = pos.x + cfg.GetWndOffsetX();
            auto top    = pos.y + cfg.GetWndOffsetY();
            auto right  = left + width;
            auto bottom = top + height;
            RECT rect;
            if( GetDesktopFromPoint( pos, rect ) ) {
                if( left < rect.left )
                    left = rect.left;
                if( top < rect.top )
                    top  = rect.top;
                if( rect.right < right )
                    left -= (right - rect.right);
                Position newPos{};
                if( bottom < rect.bottom )
                    newPos = Position::BELOW;
                else {
                    top -= (height + cfg.GetWndOffsetY());
                    newPos = Position::ABOVE;
                }
                WinAPI::SetWindowPos( hwnd, HWND_TOPMOST,
                                      left, top, width, height, SWP_NOACTIVATE );
                if( m_curPosition != newPos )
                    OnChangePosition( hwnd, newPos );
                m_curPosition = newPos;
            }
        }
        WinRestore();
    }


} // namespace clime

