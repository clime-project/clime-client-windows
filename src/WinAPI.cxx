//------------------------------------------------------------------------------
//
// WinAPI.cxx
//
//------------------------------------------------------------------------------
#include "WinAPI.hxx"

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>

namespace clime {

    // Winbase.h
    HGLOBAL WinAPI::GlobalAlloc( UINT uFlags, SIZE_T dwBytes ) {
        return ::GlobalAlloc( uFlags, dwBytes );
    }
    HGLOBAL WinAPI::GlobalFree( HGLOBAL hMem ) {
        return ::GlobalFree( hMem );
    }
    LPVOID WinAPI::GlobalLock( HGLOBAL hMem ) {
        return ::GlobalLock( hMem );
    }
    BOOL WinAPI::GlobalUnlock( HGLOBAL hMem ) {
        return ::GlobalUnlock( hMem );
    }
    DWORD WinAPI::GetPrivateProfileString( LPCWSTR lpAppName, LPCWSTR lpKeyName,
                                           LPCWSTR lpDefault, LPWSTR lpReturnedString,
                                           DWORD nSize, LPCWSTR lpFileName ) {
        return ::GetPrivateProfileString( lpAppName, lpKeyName, lpDefault,
                                          lpReturnedString, nSize, lpFileName );
    }
    BOOL WinAPI::QueryFullProcessImageNameW( HANDLE hProcess, DWORD dwFlags,
                                             LPWSTR lpExeName, PDWORD lpdwSize ) {
        return ::QueryFullProcessImageNameW( hProcess, dwFlags, lpExeName, lpdwSize );
    }

    // Wingdi.h
    HGDIOBJ WinAPI::SelectObject( HDC hdc, HGDIOBJ h ) {
        return ::SelectObject( hdc, h );
    }
    BOOL WinAPI::Polyline( HDC hdc, const POINT* pPoint, int cpt ) {
        return ::Polyline( hdc, pPoint, cpt );
    }
    HPEN WinAPI::CreatePen( int iStyle, int cWidth, COLORREF color ) {
        return ::CreatePen( iStyle, cWidth, color );
    }
    HBRUSH WinAPI::CreateSolidBrush( COLORREF color ) {
        return ::CreateSolidBrush( color );
    }
    HFONT WinAPI::CreateFont( int cHeight, int cWidth, int cEscapement,
                              int cOrientation, int cWeight, DWORD bItalic,
                              DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet,
                              DWORD iOutPrecision, DWORD iClipPrecision,
                              DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFaceName ) {
        return ::CreateFontW( cHeight, cWidth, cEscapement,
                              cOrientation, cWeight, bItalic,
                              bUnderline, bStrikeOut, iCharSet,
                              iOutPrecision, iClipPrecision,
                              iQuality, iPitchAndFamily, pszFaceName );
    }
    COLORREF WinAPI::SetBkColor( HDC hdc, COLORREF color ) {
        return ::SetBkColor( hdc, color );
    }
    COLORREF WinAPI::SetTextColor( HDC hdc, COLORREF color ) {
        return ::SetTextColor( hdc, color );
    }
    BOOL WinAPI::TextOut( HDC hdc, int x, int y, LPCWSTR lpString, int c ) {
        return ::TextOutW( hdc, x, y, lpString, c );
    }
    BOOL WinAPI::GetTextExtentPoint32( HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl ) {
        return ::GetTextExtentPoint32W( hdc, lpString, c, psizl );
    }
    HRGN WinAPI::CreateRoundRectRgn( int x1, int y1, int x2, int y2, int w, int h ) {
        return ::CreateRoundRectRgn( x1, y1, x2, y2, w, h );
    }
    HRGN WinAPI::CreatePolygonRgn( const POINT* pPoint, int cPoint, int iMode ) {
        return ::CreatePolygonRgn( pPoint, cPoint, iMode );
    }
    HRGN WinAPI::CreateRectRgn( int x1, int y1, int x2, int y2 ) {
        return ::CreateRectRgn( x1, y1, x2, y2 );
    }
    int WinAPI::CombineRgn( HRGN hrgnDst, HRGN hrgnSrc1, HRGN hrgnSrc2, int iMode ) {
        return ::CombineRgn( hrgnDst, hrgnSrc1, hrgnSrc2, iMode );
    }
    int WinAPI::SetBkMode( HDC hdc, int mode ) {
        return ::SetBkMode( hdc, mode );
    }
    HGDIOBJ WinAPI::GetStockObject( int i ) {
        return ::GetStockObject( i );
    }
    BOOL WinAPI::DeleteObject( HGDIOBJ ho ) {
        return ::DeleteObject( ho );
    }

    // Winuser.h
    int WinAPI::FillRect( HDC hDC, const RECT* pRect, HBRUSH hbr ) {
        return ::FillRect( hDC, pRect, hbr );
    }
    BOOL WinAPI::SetRect( LPRECT lprc, int xLeft,
                          int yTop, int xRight, int yBottom ) {
        return ::SetRect( lprc, xLeft, yTop, xRight, yBottom );
    }
    BOOL WinAPI::RegisterHotKey( HWND hWnd, int id, UINT fsModifiers, UINT vk ) {
        return ::RegisterHotKey( hWnd, id, fsModifiers, vk );
    }
    BOOL WinAPI::UnregisterHotKey( HWND hWnd, int id ) {
        return ::UnregisterHotKey( hWnd, id );
    }
    BOOL WinAPI::SetWindowText( HWND hWnd, LPCWSTR lpString ) {
        return ::SetWindowTextW( hWnd, lpString );
    }
    int WinAPI::GetWindowText( HWND hWnd, LPWSTR lpString, int nMaxCount ) {
        return ::GetWindowTextW( hWnd, lpString, nMaxCount );
    }
    BOOL WinAPI::EnumDisplayMonitors( HDC hdc, LPCRECT lprcClip,
                                      MONITORENUMPROC lpfnEnum, LPARAM dwData ) {
        return ::EnumDisplayMonitors( hdc, lprcClip, lpfnEnum, dwData );
    }
    HMONITOR WinAPI::MonitorFromPoint( POINT pt, DWORD dwFlags ) {
        return ::MonitorFromPoint( pt, dwFlags );
    }
    BOOL WinAPI::ShowWindow( HWND hWnd, int nCmdShow ) {
        return ::ShowWindow( hWnd, nCmdShow );
    }
    BOOL WinAPI::UpdateWindow( HWND hWnd ) {
        return ::UpdateWindow( hWnd );
    }
    BOOL WinAPI::EnableWindow( HWND hWnd, BOOL bEnable ) {
        return ::EnableWindow( hWnd, bEnable );
    }
    HWND WinAPI::GetForegroundWindow() {
        return ::GetForegroundWindow();
    }
    BOOL WinAPI::SetForegroundWindow( HWND hWnd ) {
        return ::SetForegroundWindow( hWnd );
    }
    HWND WinAPI::GetFocus() {
        return ::GetFocus();
    }
    HWND WinAPI::SetFocus( HWND hWnd ) {
        return ::SetFocus( hWnd );
    }
    BOOL WinAPI::GetCaretPos( LPPOINT lpPoint ) {
        return ::GetCaretPos( lpPoint );
    }
    BOOL WinAPI::ClientToScreen( HWND hWnd, LPPOINT lpPoint ) {
        return ::ClientToScreen( hWnd, lpPoint );
    }
    BOOL WinAPI::SetWindowPos( HWND hWnd, HWND hWndInsertAfter,
                               int X, int Y, int cx, int cy, UINT uFlags ) {
        return ::SetWindowPos( hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags );
    }
    HCURSOR WinAPI::LoadCursor( HINSTANCE hInstance, LPCWSTR lpCursorName ) {
        return ::LoadCursorW( hInstance, lpCursorName );
    }
    HICON WinAPI::LoadIcon( HINSTANCE hInstance, LPCWSTR lpIconName ) {
        return ::LoadIconW( hInstance, lpIconName );
    }
    BOOL WinAPI::GetWindowRect( HWND hWnd, LPRECT lpRect ) {
        return ::GetWindowRect( hWnd, lpRect );
    }
    BOOL WinAPI::GetClientRect( HWND hWnd, LPRECT lpRect ) {
        return ::GetClientRect( hWnd, lpRect );
    }
    BOOL WinAPI::InvalidateRect( HWND hWnd, const RECT* pRect, BOOL bErase ) {
        return ::InvalidateRect( hWnd, pRect, bErase );
    }
    int WinAPI::GetWindowRgn( HWND hWnd, HRGN hRgn ) {
        return ::GetWindowRgn( hWnd, hRgn );
    }
    int WinAPI::SetWindowRgn( HWND hWnd, HRGN hRgn, BOOL bRedraw ) {
        return ::SetWindowRgn( hWnd, hRgn, bRedraw );
    }
    HDC WinAPI::BeginPaint( HWND hWnd, LPPAINTSTRUCT lpPaint ) {
        return ::BeginPaint( hWnd, lpPaint );
    }
    BOOL WinAPI::EndPaint( HWND hWnd, const PAINTSTRUCT *lpPaint ) {
        return ::EndPaint( hWnd, lpPaint );
    }
    BOOL WinAPI::AttachThreadInput( DWORD idAttach, DWORD idAttachTo, BOOL fAttach ) {
        return ::AttachThreadInput( idAttach, idAttachTo, fAttach );
    }
    DWORD WinAPI::GetWindowThreadProcessId( HWND hWnd, LPDWORD lpdwProcessId ) {
        return ::GetWindowThreadProcessId( hWnd, lpdwProcessId );
    }
    BOOL WinAPI::SetLayeredWindowAttributes( HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags ) {
        return ::SetLayeredWindowAttributes( hwnd, crKey, bAlpha, dwFlags );
    }
    BOOL WinAPI::IsIconic( HWND hWnd ) {
        return ::IsIconic( hWnd );
    }
    BOOL WinAPI::GetMessage( LPMSG lpMsg, HWND hWnd,
                             UINT wMsgFilterMin, UINT wMsgFilterMax ) {
        return ::GetMessage( lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax );
    }
    LRESULT WinAPI::SendMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
        return ::SendMessage( hWnd, Msg, wParam, lParam );
    }
    BOOL WinAPI::PostMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
        return ::PostMessage( hWnd, Msg, wParam, lParam );
    }
    BOOL WinAPI::TranslateMessage( const MSG* pMsg ) {
        return ::TranslateMessage( pMsg );
    }
    LRESULT WinAPI::DispatchMessage( const MSG* pMsg ) {
        return ::DispatchMessage( pMsg );
    }
    void WinAPI::PostQuitMessage( int nExitCode ) {
        ::PostQuitMessage( nExitCode );
    }
    ATOM WinAPI::RegisterClass_Ex( const WNDCLASSEXW *Arg1 ) {
        return ::RegisterClassExW( Arg1 );
    }
    BOOL WinAPI::UnregisterClass( LPCWSTR lpClassName, HINSTANCE hInstance ) {
        return ::UnregisterClassW( lpClassName, hInstance );
    }
    LRESULT WinAPI::DefWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) {
        return ::DefWindowProc( hWnd, Msg, wParam, lParam );
    }
    LONG_PTR WinAPI::GetWindowLongPtr( HWND hWnd, int nIndex ) {
        return ::GetWindowLongPtr( hWnd, nIndex );
    }
    LONG_PTR WinAPI::SetWindowLongPtr( HWND hWnd, int nIndex, LONG_PTR dwNewLong ) {
        return ::SetWindowLongPtr( hWnd, nIndex, dwNewLong );
    }
    HWND WinAPI::Create_Window( LPCWSTR lpClassName,
                                LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y,
                                int nWidth, int nHeight, HWND hWndParent,
                                HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam ) {
        return ::CreateWindowW( lpClassName, lpWindowName, dwStyle, X, Y,
                                nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam );
    }
    HWND WinAPI::CreateWindowEx( DWORD dwExStyle, LPCWSTR lpClassName,
                                 LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y,
                                 int nWidth, int nHeight, HWND hWndParent,
                                 HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam ) {
        return ::CreateWindowExW( dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y,
                                  nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam );
    }
    HWND WinAPI::GetDesktopWindow() {
        return ::GetDesktopWindow();
    }
    BOOL WinAPI::EnumChildWindows( HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam ) {
        return ::EnumChildWindows( hWndParent, lpEnumFunc, lParam );
    }
    int WinAPI::LoadString( HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax ) {
        return ::LoadStringW( hInstance, uID, lpBuffer, cchBufferMax );
    }
    int WinAPI::MessageBox( HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType ) {
        return ::MessageBoxW( hWnd, lpText, lpCaption, uType );
    }
    UINT WinAPI::RealGetWindowClass( HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax ) {
        return ::RealGetWindowClassW( hwnd, ptszClassName, cchClassNameMax );
    }
    UINT_PTR WinAPI::SetTimer( HWND hWnd, UINT_PTR nIDEvent,
                               UINT uElapse, TIMERPROC lpTimerFunc ) {
        return ::SetTimer( hWnd, nIDEvent, uElapse, lpTimerFunc );
    }
    BOOL WinAPI::KillTimer( HWND hWnd, UINT_PTR uIDEvent ) {
        return ::KillTimer( hWnd, uIDEvent );
    }
    BOOL WinAPI::OpenClipboard( HWND hWndNewOwner ) {
        return ::OpenClipboard( hWndNewOwner );
    }
    BOOL WinAPI::EmptyClipboard() {
        return ::EmptyClipboard();
    }
    HANDLE WinAPI::SetClipboardData( UINT uFormat, HANDLE hMem ) {
        return ::SetClipboardData( uFormat, hMem );
    }
    BOOL WinAPI::CloseClipboard() {
        return ::CloseClipboard();
    }

    // Stringapiset.h
    int WinAPI::MultiByteToWideChar( UINT CodePage, DWORD dwFlags, LPCSTR pMultiByteStr,
                                     int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar ) {
        return ::MultiByteToWideChar( CodePage, dwFlags, pMultiByteStr,
                                      cbMultiByte, lpWideCharStr, cchWideChar );
    }
    int WinAPI::WideCharToMultiByte( UINT CodePage, DWORD dwFlags,
                                     LPCWSTR lpWideCharStr, int cchWideChar,
                                     LPSTR lpMultiByteStr, int cbMultiByte,
                                     LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar ) {
        return ::WideCharToMultiByte( CodePage, dwFlags,
                                      lpWideCharStr, cchWideChar,
                                      lpMultiByteStr, cbMultiByte,
                                      lpDefaultChar, lpUsedDefaultChar );
    }
    // Sysinfoapi.h
    DWORD WinAPI::GetTickCount() {
        return ::GetTickCount();
    }

    // Synchapi.h
    void WinAPI::Sleep( DWORD dwMilliseconds ) {
        ::Sleep( dwMilliseconds );
    }

    // Shellapi.h
    HINSTANCE WinAPI::Shell_Execute( HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile,
                                     LPCWSTR lpParameters, LPCWSTR lpDirectory, INT nShowCmd ) {
        return ::ShellExecuteW( hwnd, lpOperation,
                                lpFile, lpParameters, lpDirectory, nShowCmd );
    }
    // Fileapi.h
    DWORD WinAPI::GetFileAttributes( LPCWSTR lpFileName ) {
        return ::GetFileAttributesW( lpFileName );
    }

    // Processthreadsapi.h
    HANDLE WinAPI::OpenProcess( DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId ) {
        return ::OpenProcess( dwDesiredAccess, bInheritHandle, dwProcessId );
    }
    DWORD WinAPI::GetCurrentThreadId() {
        return ::GetCurrentThreadId();
    }
    void WinAPI::GetStartupInfo( LPSTARTUPINFO lpStartupInfo ) {
        ::GetStartupInfo( lpStartupInfo );
    }

    // handleapi.h
    BOOL WinAPI::CloseHandle( HANDLE hObject ) {
        return ::CloseHandle( hObject );
    }

    // Libloaderapi.h
    HMODULE WinAPI::GetModuleHandle( LPCWSTR lpModuleName ) {
        return ::GetModuleHandleW( lpModuleName );
    }
    DWORD WinAPI::GetModuleFileName( HMODULE hModule, LPWSTR lpFilename, DWORD nSize ) {
        return ::GetModuleFileNameW( hModule, lpFilename, nSize );
    }

    // Windowsx.h 
    DWORD WinAPI::EditGetSel( HWND hwndCtl ) {
        return Edit_GetSel( hwndCtl );
    }
    void WinAPI::EditSetSel( HWND hwndCtl, DWORD selection ) {
        Edit_SetSel( hwndCtl, LOWORD(selection), HIWORD(selection) );
    }

} // namespace clime

