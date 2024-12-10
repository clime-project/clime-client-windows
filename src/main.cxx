//------------------------------------------------------------------------------
//
// main.cxx
//
//------------------------------------------------------------------------------

#include "Common.hxx"
#include "MainWindow.hxx"
#include "Config.hxx"
#include "Resource.hxx"
#include "WinAPI.hxx"

#include <sstream>
#include <cstring>

//------------------------------------------------------------------------------
//
// constants
//
//------------------------------------------------------------------------------
constexpr const wchar_t*  INI_FILENAME = L"./winclime.ini";

//------------------------------------------------------------------------------
//
// internal functions declaration
//
//------------------------------------------------------------------------------
static WINBOOL CALLBACK CheckWindow( HWND hwnd, LPARAM lparam );

//------------------------------------------------------------------------------
//
// application entry point
//
//------------------------------------------------------------------------------
#if 0
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE /*prevInstance*/, PSTR /*cmdLine*/, int cmdShow ) {
#else
    int main( int /*argc*/, char** /*argv*/, char** /*env*/ ){

        STARTUPINFO startUpInfo;
        clime::WinAPI::GetStartupInfo( &startUpInfo );
        HINSTANCE hInstance = clime::WinAPI::GetModuleHandle( 0 );
//      HINSTANCE hPrevInstance = 0;
//      LPCSTR lpszCmdParam = ""; // 引数は無視?
        int cmdShow = (startUpInfo.dwFlags & STARTF_USESHOWWINDOW) ?
            startUpInfo.wShowWindow : SW_SHOWNORMAL;
#endif

        HWND wndDesktop = clime::WinAPI::GetDesktopWindow();
        if( !clime::WinAPI::EnumChildWindows( wndDesktop, CheckWindow, 0 ) ) {
            wchar_t msg[256];
            clime::WinAPI::LoadString( hInstance, IDS_ERRMSG_ALREADY_LAUNCHED, msg, 256 );
            clime::WinAPI::MessageBox( wndDesktop, msg, clime::APPNAME, MB_ICONERROR | MB_OK );
            return 0;
        }

        int ret = 0;
        try {
            wchar_t module[1024];
            clime::WinAPI::GetModuleFileName( hInstance, module, 1024 );
            clime::Config     cfg{ INI_FILENAME };
            clime::MainWindow mainWnd{ hInstance, module, cfg };
            ret = mainWnd.DoModal( cmdShow );
        } catch( std::exception& err ) {
            std::wostringstream oss;
            const char* pMsg = err.what();
            uint32_t len = ::strlen( pMsg );
            wchar_t buf[1024];
            uint32_t cnt = clime::WinAPI::MultiByteToWideChar( CP_UTF8,
                                                               MB_ERR_INVALID_CHARS,
                                                               pMsg, len, buf, 1024 );
            (void)cnt;
            oss << L"ERROR : " << buf;
            clime::WinAPI::MessageBox( wndDesktop, oss.str().c_str(),
                                       clime::APPNAME, MB_ICONERROR | MB_OK );
        }
        return ret;
    }



    //------------------------------------------------------------------------------
    //
    // internal functions implementation
    //
    //------------------------------------------------------------------------------
    static WINBOOL CALLBACK CheckWindow( HWND hwnd, LPARAM /*lparam*/ ) {
        wchar_t buf[128];
        buf[0] = 0;
        clime::WinAPI::RealGetWindowClass( hwnd, buf, 128 );
        if( !::wcscmp( buf, clime::APPNAME ) )
            return FALSE;
        else
            return TRUE;
    }

