//------------------------------------------------------------------------------
//
// WindowMover.hxx
//
//------------------------------------------------------------------------------
#ifndef WINDOWMOVER_HXX__
#define WINDOWMOVER_HXX__

#include "WinAPI.hxx"

namespace clime {

    class Config;

    class WindowMover {
    protected:
        enum class Position {
            BELOW = 0,
            ABOVE = 1
        };
    public:
        WindowMover();
        WindowMover( const WindowMover& ) = delete;
        ~WindowMover();
        WindowMover& operator=( const WindowMover& ) = delete;
    protected:
        inline HWND GetTargetWindow() const { return m_targetWin; }
        inline Position GetPosition() const { return m_curPosition; }
    protected:
        void UpdateMonitorInfo();
        HWND WinSave();
        void WinRestore();
        void MoveToCursor( HWND hwnd,
                           const Config& cfg, int width, int height );
    private:
        virtual void OnChangePosition( HWND hwnd, Position pos ) = 0;
    private:
        bool GetDesktopFromPoint( const POINT& pt, RECT& rect ) const;
        static WINBOOL CALLBACK MonitorInfoCallback( HMONITOR, HDC, LPRECT, LPARAM );
    private:
        Position    m_curPosition;
        HWND        m_activeWin;
        HWND        m_targetWin;
        DWORD       m_targetThread;
        DWORD       m_selfThread;
        DWORD       m_selection;
    };

} // namespace clime

#endif // WINDOWMOVER_HXX__
