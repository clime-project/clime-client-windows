//------------------------------------------------------------------------------
//
// WinAPI.hxx
//
//------------------------------------------------------------------------------
#ifndef WINAPI_HXX__
#define WINAPI_HXX__

#include <stdint.h>
#include <windef.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef  WIN32_LEAN_AND_MEAN

namespace clime {

    class WinAPI {
    public:  // Winbase.h
        static HGLOBAL GlobalAlloc( UINT uFlags, SIZE_T dwBytes );
        static HGLOBAL GlobalFree( HGLOBAL hMem );
        static LPVOID GlobalLock( HGLOBAL hMem );
        static BOOL GlobalUnlock( HGLOBAL hMem );
        static DWORD GetPrivateProfileString( LPCWSTR lpAppName, LPCWSTR lpKeyName,
                                              LPCWSTR lpDefault, LPWSTR lpReturnedString,
                                              DWORD nSize, LPCWSTR lpFileName );
        static BOOL QueryFullProcessImageNameW( HANDLE hProcess, DWORD dwFlags,
                                                LPWSTR lpExeName, PDWORD lpdwSize );

    public:  // Wingdi.h
        static HGDIOBJ SelectObject( HDC hdc, HGDIOBJ h );
        static BOOL Polyline( HDC hdc, const POINT* pPoint, int cpt );
        static HPEN CreatePen( int iStyle, int cWidth, COLORREF color );
        static HBRUSH CreateSolidBrush( COLORREF color );
        static HFONT CreateFont( int cHeight, int cWidth, int cEscapement,
                                 int cOrientation, int cWeight, DWORD bItalic,
                                 DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet,
                                 DWORD iOutPrecision, DWORD iClipPrecision,
                                 DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFaceName );
        static COLORREF SetBkColor( HDC hdc, COLORREF color );
        static COLORREF SetTextColor( HDC hdc, COLORREF color );
        static BOOL TextOut( HDC hdc, int x, int y, LPCWSTR lpString, int c );
        static BOOL GetTextExtentPoint32( HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl );
        static HRGN CreateRoundRectRgn( int x1, int y1, int x2, int y2, int w, int h );
        static HRGN CreatePolygonRgn( const POINT* pPoint, int cPoint, int iMode );
        static HRGN CreateRectRgn( int x1, int y1, int x2, int y2 );
        static int CombineRgn( HRGN hrgnDst, HRGN hrgnSrc1, HRGN hrgnSrc2, int iMode );
        static int SetBkMode( HDC hdc, int mode );
        static HGDIOBJ GetStockObject( int i );
        static BOOL DeleteObject( HGDIOBJ ho );

    public:  // Winuser.h
        static int FillRect( HDC hDC, const RECT* pRect, HBRUSH hbr );
        static BOOL SetRect( LPRECT lprc, int xLeft,
                             int yTop, int xRight, int yBottom );
        static BOOL RegisterHotKey( HWND hWnd, int id, UINT fsModifiers, UINT vk );
        static BOOL UnregisterHotKey( HWND hWnd, int id );
        static BOOL SetWindowText( HWND hWnd, LPCWSTR lpString );
        static int GetWindowText( HWND hWnd, LPWSTR lpString, int nMaxCount );
        static BOOL EnumDisplayMonitors( HDC hdc, LPCRECT lprcClip,
                                         MONITORENUMPROC lpfnEnum, LPARAM dwData );
        static HMONITOR MonitorFromPoint( POINT pt, DWORD dwFlags );
        static BOOL ShowWindow( HWND hWnd, int nCmdShow );
        static BOOL UpdateWindow( HWND hWnd );
        static BOOL EnableWindow( HWND hWnd, BOOL bEnable );
        static HWND GetForegroundWindow();
        static BOOL SetForegroundWindow( HWND hWnd );
        static HWND GetFocus();
        static HWND SetFocus( HWND hWnd );
        static BOOL GetCaretPos( LPPOINT lpPoint );
        static BOOL ClientToScreen( HWND hWnd, LPPOINT lpPoint );
        static BOOL SetWindowPos( HWND hWnd, HWND hWndInsertAfter,
                                  int X, int Y, int cx, int cy, UINT uFlags );
        static HCURSOR LoadCursor( HINSTANCE hInstance, LPCWSTR lpCursorName );
        static HICON LoadIcon( HINSTANCE hInstance, LPCWSTR lpIconName );
        static BOOL GetWindowRect( HWND hWnd, LPRECT lpRect );
        static BOOL GetClientRect( HWND hWnd, LPRECT lpRect );
        static BOOL InvalidateRect( HWND hWnd, const RECT* pRect, BOOL bErase );
        static int GetWindowRgn( HWND hWnd, HRGN hRgn );
        static int SetWindowRgn( HWND hWnd, HRGN hRgn, BOOL bRedraw );
        static HDC BeginPaint( HWND hWnd, LPPAINTSTRUCT lpPaint );
        static BOOL EndPaint( HWND hWnd, const PAINTSTRUCT *lpPaint );
        static BOOL AttachThreadInput( DWORD idAttach, DWORD idAttachTo, BOOL fAttach );
        static DWORD GetWindowThreadProcessId( HWND hWnd, LPDWORD lpdwProcessId );
        static BOOL SetLayeredWindowAttributes( HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags );
        static BOOL IsIconic( HWND hWnd );
        static BOOL GetMessage( LPMSG lpMsg, HWND hWnd,
                                UINT wMsgFilterMin, UINT wMsgFilterMax );
        static LRESULT SendMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
        static BOOL PostMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
        static BOOL TranslateMessage( const MSG* pMsg );
        static LRESULT DispatchMessage( const MSG* pMsg );
        static void PostQuitMessage( int nExitCode );
        static ATOM RegisterClass_Ex( const WNDCLASSEXW *Arg1 );
        static BOOL UnregisterClass( LPCWSTR lpClassName, HINSTANCE hInstance );
        static LRESULT DefWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
        static LONG_PTR GetWindowLongPtr( HWND hWnd, int nIndex );
        static LONG_PTR SetWindowLongPtr( HWND hWnd, int nIndex, LONG_PTR dwNewLong );
        static HWND Create_Window( LPCWSTR lpClassName,
                                   LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y,
                                   int nWidth, int nHeight, HWND hWndParent,
                                   HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam );
        static HWND CreateWindowEx( DWORD dwExStyle, LPCWSTR lpClassName,
                                    LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y,
                                    int nWidth, int nHeight, HWND hWndParent,
                                    HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam );
        static HWND GetDesktopWindow();
        static BOOL EnumChildWindows( HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam );
        static int LoadString( HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax );
        static int MessageBox( HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType );
        static UINT RealGetWindowClass( HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax );
        static UINT_PTR SetTimer( HWND hWnd, UINT_PTR nIDEvent,
                                  UINT uElapse, TIMERPROC lpTimerFunc );
        static BOOL KillTimer( HWND hWnd, UINT_PTR uIDEvent );
        static BOOL OpenClipboard( HWND hWndNewOwner );
        static BOOL EmptyClipboard();
        static HANDLE SetClipboardData( UINT uFormat, HANDLE hMem );
        static BOOL CloseClipboard();

    public:  // Stringapiset.h
        static int MultiByteToWideChar( UINT CodePage, DWORD dwFlags, LPCSTR pMultiByteStr,
                                        int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar );
        static int WideCharToMultiByte( UINT CodePage, DWORD dwFlags,
                                        LPCWSTR lpWideCharStr, int cchWideChar,
                                        LPSTR lpMultiByteStr, int cbMultiByte,
                                        LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar );
    public:  // Sysinfoapi.h
        static DWORD GetTickCount();

    public:  // Synchapi.h
        static void Sleep( DWORD dwMilliseconds );

    public:  // Shellapi.h
        static HINSTANCE Shell_Execute( HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile,
                                        LPCWSTR lpParameters, LPCWSTR lpDirectory, INT nShowCmd );
    public:  // Fileapi.h
        static DWORD GetFileAttributes( LPCWSTR lpFileName );

    public:  // Processthreadsapi.h
        static HANDLE OpenProcess( DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId );
        static DWORD GetCurrentThreadId();
        static void GetStartupInfo( LPSTARTUPINFO lpStartupInfo );

    public:  // handleapi.h
        static BOOL CloseHandle( HANDLE hObject );

    public: // Libloaderapi.h
        static HMODULE GetModuleHandle( LPCWSTR lpModuleName );
        static DWORD GetModuleFileName( HMODULE hModule, LPWSTR lpFilename, DWORD nSize );

    public: // Windowsx.h 
        static DWORD EditGetSel( HWND hwndCtl );
        static void EditSetSel( HWND hwndCtl, DWORD selection );
    };

} // namespace clime

#endif // WINAPI_HXX__
