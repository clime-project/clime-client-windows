//------------------------------------------------------------------------------
//
// MainWindow.cxx
//
//------------------------------------------------------------------------------
#ifndef WINCLIME_MAJOR_VER
    #define WINCLIME_MAJOR_VER 0
#endif

#ifndef WINCLIME_MINOR_VER
    #define WINCLIME_MINOR_VER 0
#endif

#include "Utilities.hxx"

#include "MainWindow.hxx"

#include "Common.hxx"
#include "Resource.hxx"
#include "Config.hxx"
#include "EngineInfo.hxx"
#include "ColorTheme.hxx"
#include "Candidates.hxx"
#include "TextBox.hxx"
#include "ListBox.hxx"
#include "Colors.hxx"
#include "InputBox.hxx"
#include "WinAPI.hxx"
#include "EngineProxy.hxx"
#include "UTF16.hxx"

#include <ctime>
#include <string.h>
#include <algorithm>

//------------------------------------------------------------------------------
//
// constants
//
//------------------------------------------------------------------------------

constexpr COLORREF CLR_LGRAY = RGB( 0xC0, 0xC0, 0xC0 );

// 0x0* : number keys ---------------------------------------
constexpr const unsigned char HOTKEY_NUM_1  = 0x01;
constexpr const unsigned char HOTKEY_NUM_2  = 0x02;
constexpr const unsigned char HOTKEY_NUM_3  = 0x03;
constexpr const unsigned char HOTKEY_NUM_4  = 0x04;
constexpr const unsigned char HOTKEY_NUM_5  = 0x05;
constexpr const unsigned char HOTKEY_NUM_6  = 0x06;
constexpr const unsigned char HOTKEY_NUM_7  = 0x07;
constexpr const unsigned char HOTKEY_NUM_8  = 0x08;
constexpr const unsigned char HOTKEY_NUM_9  = 0x09;

// 0x1* : Ctrl + number keys -------------------------------
constexpr const unsigned char HOTKEY_CTRL_0 = 0x10;
constexpr const unsigned char HOTKEY_CTRL_1 = 0x11;
constexpr const unsigned char HOTKEY_CTRL_2 = 0x12;
constexpr const unsigned char HOTKEY_CTRL_3 = 0x13;
constexpr const unsigned char HOTKEY_CTRL_4 = 0x14;
constexpr const unsigned char HOTKEY_CTRL_5 = 0x15;
constexpr const unsigned char HOTKEY_CTRL_6 = 0x16;
constexpr const unsigned char HOTKEY_CTRL_7 = 0x17;
constexpr const unsigned char HOTKEY_CTRL_8 = 0x18;
constexpr const unsigned char HOTKEY_CTRL_9 = 0x19;

//MEMO : 0x21 ～ 0x7E は使ってはならない ------------------------

// 0x80 ～ 0x9F : Ctrl + alphabet & etc. --------------------
constexpr const unsigned char HOTKEY_CTRL_A = 0x80;
constexpr const unsigned char HOTKEY_CTRL_B = 0x81;
constexpr const unsigned char HOTKEY_CTRL_C = 0x82;
constexpr const unsigned char HOTKEY_CTRL_D = 0x83;
constexpr const unsigned char HOTKEY_CTRL_E = 0x84;
constexpr const unsigned char HOTKEY_CTRL_F = 0x85;
constexpr const unsigned char HOTKEY_CTRL_G = 0x86;
//constexpr const unsigned char HOTKEY_CTRL_H = 0x87;
constexpr const unsigned char HOTKEY_CTRL_I = 0x88;
constexpr const unsigned char HOTKEY_CTRL_J = 0x89;
constexpr const unsigned char HOTKEY_CTRL_K = 0x8A;
//constexpr const unsigned char HOTKEY_CTRL_L = 0x8B;
//constexpr const unsigned char HOTKEY_CTRL_M = 0x8C;
constexpr const unsigned char HOTKEY_CTRL_N = 0x8D;
constexpr const unsigned char HOTKEY_CTRL_O = 0x8E;
constexpr const unsigned char HOTKEY_CTRL_P = 0x8F;
constexpr const unsigned char HOTKEY_CTRL_Q = 0x90;
//constexpr const unsigned char HOTKEY_CTRL_R = 0x91;
//constexpr const unsigned char HOTKEY_CTRL_S = 0x92;
constexpr const unsigned char HOTKEY_CTRL_T = 0x93;
//constexpr const unsigned char HOTKEY_CTRL_U = 0x94;
//constexpr const unsigned char HOTKEY_CTRL_V = 0x95;
//constexpr const unsigned char HOTKEY_CTRL_W = 0x96;
//constexpr const unsigned char HOTKEY_CTRL_X = 0x97;
//constexpr const unsigned char HOTKEY_CTRL_Y = 0x98;
//constexpr const unsigned char HOTKEY_CTRL_Z = 0x99;
constexpr const unsigned char HOTKEY_CTRL_SEMICOLON = 0x9A;
constexpr const unsigned char HOTKEY_CTRL_COLON     = 0x9B;
constexpr const unsigned char HOTKEY_CTRL_SPACE     = 0x9C;

// 0xA0 ～ 0xBF : Alt + alphabet & etc. ---------------------
constexpr const unsigned char HOTKEY_ALT_J  = 0xA0;
constexpr const unsigned char HOTKEY_ALT_Q  = 0xA1;
constexpr const unsigned char HOTKEY_ALT_D  = 0xA2;
constexpr const unsigned char HOTKEY_ALT_W  = 0xA3;

// 0xC0 ～ 0xDF : other keys --------------------------------
constexpr const unsigned char HOTKEY_LEFT   = 0xC0;
constexpr const unsigned char HOTKEY_UP     = 0xC1;
constexpr const unsigned char HOTKEY_RIGHT  = 0xC2;
constexpr const unsigned char HOTKEY_DOWN   = 0xC3;
constexpr const unsigned char HOTKEY_HOME   = 0xC4;
constexpr const unsigned char HOTKEY_END    = 0xC5;
constexpr const unsigned char HOTKEY_RETURN = 0xC6;
constexpr const unsigned char HOTKEY_DELETE = 0xC7;
constexpr const unsigned char HOTKEY_BACKSP = 0xC8;
constexpr const unsigned char HOTKEY_SPACE  = 0xC9;
constexpr const unsigned char HOTKEY_CPSLCK = 0xC0;
constexpr const unsigned char HOTKEY_ESCAPE = 0xCA;

// 0xE* : Alt + Function ------------------------------------
constexpr const unsigned char HOTKEY_ALT_F01 = 0xE1;
//constexpr const unsigned char HOTKEY_ALT_F02 = 0xE2;
//constexpr const unsigned char HOTKEY_ALT_F03 = 0xE3;
//constexpr const unsigned char HOTKEY_ALT_F04 = 0xE4;
//constexpr const unsigned char HOTKEY_ALT_F05 = 0xE5;
//constexpr const unsigned char HOTKEY_ALT_F06 = 0xE6;
//constexpr const unsigned char HOTKEY_ALT_F07 = 0xE7;
//constexpr const unsigned char HOTKEY_ALT_F08 = 0xE8;
//constexpr const unsigned char HOTKEY_ALT_F09 = 0xE9;
//constexpr const unsigned char HOTKEY_ALT_F10 = 0xEA;
//constexpr const unsigned char HOTKEY_ALT_F11 = 0xEB;
constexpr const unsigned char HOTKEY_ALT_F12 = 0xEC;

// 0xF* : Function ------------------------------------------
constexpr const unsigned char HOTKEY_F01    = 0xF1;
//constexpr const unsigned char HOTKEY_F02    = 0xF2;
//constexpr const unsigned char HOTKEY_F03    = 0xF3;
//constexpr const unsigned char HOTKEY_F04    = 0xF4;
//constexpr const unsigned char HOTKEY_F05    = 0xF5;
//constexpr const unsigned char HOTKEY_F06    = 0xF6;
//constexpr const unsigned char HOTKEY_F07    = 0xF7;
//constexpr const unsigned char HOTKEY_F08    = 0xF8;
constexpr const unsigned char HOTKEY_F09    = 0xF9;
//constexpr const unsigned char HOTKEY_F10    = 0xFA;
//constexpr const unsigned char HOTKEY_F11    = 0xFB;
//constexpr const unsigned char HOTKEY_F12    = 0xFC;


namespace clime {

    MainWindow::MainWindow( HINSTANCE hInstance,
                            const wchar_t* pModulePath,
                            const Config& cfg ) : WindowMover(),
                                                  m_hThisInstance( hInstance ),
                                                  m_helpPath( pModulePath ),
                                                  m_config( cfg ),
                                                  m_lastDrawTime( WinAPI::GetTickCount() ),
                                                  m_lastDrawMode( DrawMode::OPAQ ),
                                                  m_pEngine( new EngineProxy{ cfg.GetEngineInfo() } ),
                                                  m_pTxtBox( new TextBox{ cfg } ),
                                                  m_pLstBox( new ListBox{ cfg } ),
                                                  m_pCands( new Candidates{} ),
                                                  m_lastResult( std::wstring{} ),
                                                  m_bIndexing( cfg.Indexing() ),
                                                  m_bDirectKeying( cfg.DirectKey() ),
                                                  m_baseHotKeys(),
                                                  m_ctrlHotKeys(),
                                                  m_emacsHotKeys(),
                                                  m_charHotKeys() {
        m_bConverting = true;
        m_exactMatch  = false;

        while( m_helpPath.back() != '\\' )
            m_helpPath.pop_back();
        m_helpPath.append( HELPPAGE );

        auto weight = (cfg.FontBold() ? FW_BOLD : FW_NORMAL);
        m_hFont = WinAPI::CreateFont( cfg.FontSize(),           // フォントの高さ
                                      0,                        // 平均文字幅(0なら高さにあわせる)
                                      0,                        // 文字送り方向の角度
                                      0,                        // ベースラインの角度
                                      weight,                   // フォントの太さ
                                      FALSE,                    // 斜体にするかどうか
                                      FALSE,                    // 下線を付けるかどうか
                                      FALSE,                    // 取り消し線を付けるかどうか
                                      SHIFTJIS_CHARSET,         // 文字セットの識別子
                                      OUT_DEFAULT_PRECIS,       // 出力精度
                                      CLIP_DEFAULT_PRECIS,      // クリッピング精度
                                      PROOF_QUALITY,            // 出力品質
                                      FIXED_PITCH | FF_MODERN,  // ピッチとファミリ
                                      cfg.FontName().c_str()    // 書体の名称
            );

        this->CalcWindowSize( m_wndWidth, m_wndHeight );

        for( auto& handler : m_keyHandlers )
            handler = &clime::MainWindow::OnEmptyKey;
        for( int key = 0x21; key < 0x7F; ++key )
            m_keyHandlers[key] = &clime::MainWindow::OnNormalKey;
        m_keyHandlers[HOTKEY_CTRL_J]         = &clime::MainWindow::OnCtrlJ;
        m_keyHandlers[HOTKEY_CTRL_A]         = &clime::MainWindow::OnCtrlA;
        m_keyHandlers[HOTKEY_CTRL_B]         = &clime::MainWindow::OnCtrlB;
        m_keyHandlers[HOTKEY_CTRL_D]         = &clime::MainWindow::OnCtrlD;
        m_keyHandlers[HOTKEY_CTRL_E]         = &clime::MainWindow::OnCtrlE;
        m_keyHandlers[HOTKEY_CTRL_F]         = &clime::MainWindow::OnCtrlF;
        m_keyHandlers[HOTKEY_CTRL_I]         = &clime::MainWindow::OnToggleIndexing;
        m_keyHandlers[HOTKEY_CTRL_K]         = &clime::MainWindow::OnCtrlK;
        m_keyHandlers[HOTKEY_CTRL_G]         = &clime::MainWindow::OnCtrlG;
        m_keyHandlers[HOTKEY_CTRL_Q]         = &clime::MainWindow::OnCtrlQ;
        m_keyHandlers[HOTKEY_CTRL_O]         = &clime::MainWindow::OnCtrlO;
        m_keyHandlers[HOTKEY_CTRL_T]         = &clime::MainWindow::OnCtrlT;
        m_keyHandlers[HOTKEY_CTRL_N]         = &clime::MainWindow::OnCtrlN;
        m_keyHandlers[HOTKEY_CTRL_P]         = &clime::MainWindow::OnCtrlP;
        m_keyHandlers[HOTKEY_BACKSP]         = &clime::MainWindow::OnBackSpaceKey;
        m_keyHandlers[HOTKEY_DELETE]         = &clime::MainWindow::OnDeleteKey;
        m_keyHandlers[HOTKEY_ESCAPE]         = &clime::MainWindow::OnEscapeKey;
        m_keyHandlers[HOTKEY_SPACE]          = &clime::MainWindow::OnSpaceKey;
        m_keyHandlers[HOTKEY_ALT_Q]          = &clime::MainWindow::OnAltQ;
//      m_keyHandlers[HOTKEY_CPSLCK]         = &clime::MainWindow::OnAltJ;
        m_keyHandlers[HOTKEY_ALT_D]          = &clime::MainWindow::OnToggleDirectKey;
        m_keyHandlers[HOTKEY_ALT_J]          = &clime::MainWindow::OnAltJ;
        m_keyHandlers[HOTKEY_ALT_W]          = &clime::MainWindow::OnAltW;
        m_keyHandlers[HOTKEY_RETURN]         = &clime::MainWindow::OnEnterKey;
        m_keyHandlers[HOTKEY_LEFT]           = &clime::MainWindow::OnCursorKey;
        m_keyHandlers[HOTKEY_UP]             = &clime::MainWindow::OnCursorKey;
        m_keyHandlers[HOTKEY_RIGHT]          = &clime::MainWindow::OnCursorKey;
        m_keyHandlers[HOTKEY_DOWN]           = &clime::MainWindow::OnCursorKey;
        m_keyHandlers[HOTKEY_HOME]           = &clime::MainWindow::OnHomeKey;
        m_keyHandlers[HOTKEY_END]            = &clime::MainWindow::OnEndKey;
        m_keyHandlers[HOTKEY_CTRL_SEMICOLON] = &clime::MainWindow::OnCtrlSemicolon;
        m_keyHandlers[HOTKEY_CTRL_COLON    ] = &clime::MainWindow::OnCtrlColon;
        m_keyHandlers[HOTKEY_CTRL_SPACE    ] = &clime::MainWindow::OnCtrlSpace;
        m_keyHandlers[HOTKEY_F01]            = &clime::MainWindow::OnHelpKey;
        m_keyHandlers[HOTKEY_F09]            = &clime::MainWindow::OnNextTheme;
        m_keyHandlers[HOTKEY_ALT_F01]        = &clime::MainWindow::OnVersionKey;
        m_keyHandlers[HOTKEY_ALT_F12]        = &clime::MainWindow::OnRecallResult;

        for( unsigned char key = HOTKEY_CTRL_0; key <= HOTKEY_CTRL_9; ++key )
            m_keyHandlers[key] = &clime::MainWindow::OnCtrlNumber;

        for( unsigned char key = HOTKEY_NUM_1; key <= HOTKEY_NUM_9; ++key )
            m_keyHandlers[key] = &clime::MainWindow::OnNumber;

        this->RegisterHotKeys();

        //■windowのスタイルを登録
        WNDCLASSEXW wndclass;
        ::memset( &wndclass, 0, sizeof(wndclass) );
        wndclass.cbSize         = sizeof(wndclass);
        wndclass.style          = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc    = WndProc;
        wndclass.cbClsExtra     = 0;
        wndclass.cbWndExtra     = sizeof(MainWindow*);
        wndclass.hInstance      = m_hThisInstance;
        wndclass.hIcon          = WinAPI::LoadIcon( m_hThisInstance, L"CLIME_ICON" );
        wndclass.hCursor        = WinAPI::LoadCursor( NULL, IDC_ARROW );
        wndclass.hbrBackground  = WinAPI::CreateSolidBrush( CLR_LGRAY );
        wndclass.lpszMenuName   = NULL;
        wndclass.lpszClassName  = APPNAME;
        wndclass.hIconSm        = WinAPI::LoadIcon( m_hThisInstance, L"CLIME_ICON" );

        //小アイコン
        WinAPI::RegisterClass_Ex( &wndclass );

        // タイトル枠などがないウィンドウ
        m_hWnd = WinAPI::CreateWindowEx( WS_EX_LAYERED,
                                         APPNAME, L"CLIME for Windows", WS_POPUP,
                                         100, // CW_USEDEFAULT,
                                         100, // CW_USEDEFAULT,
                                         m_wndWidth, m_wndHeight,
                                         NULL, NULL, m_hThisInstance, this );
    }

    MainWindow::~MainWindow() {
        WinAPI::UnregisterClass( APPNAME, m_hThisInstance );
        delete m_pEngine;
        delete m_pTxtBox;
        delete m_pLstBox;
        delete m_pCands;
    }

    LRESULT CALLBACK MainWindow::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
        MainWindow* pMainWindow = (MainWindow*)WinAPI::GetWindowLongPtr( hWnd, 0 );
        if( msg == WM_CREATE ) {
            pMainWindow = reinterpret_cast<MainWindow*>( ((CREATESTRUCT*)lParam)->lpCreateParams );
            WinAPI::SetWindowLongPtr( hWnd, 0, (ULONG_PTR)pMainWindow );
        }
        if( !pMainWindow )
            return WinAPI::DefWindowProc( hWnd, msg, wParam, lParam );
        else
            return pMainWindow->OnMessage( hWnd, msg, wParam, lParam );
    }


    int MainWindow::DoModal( int cmdShow ) {

        WinAPI::ShowWindow( m_hWnd, cmdShow );
        WinAPI::UpdateWindow( m_hWnd );

        MSG msg;
        Initialize( m_hWnd );
//      MoveToCursor( m_hWnd, m_config, m_wndWidth, m_wndHeight );
        WinAPI::SetWindowPos( m_hWnd, HWND_TOPMOST, 100, 100,
                              m_wndWidth, m_wndHeight, SWP_NOACTIVATE );
        while( WinAPI::GetMessage( &msg, NULL, 0,0 ) ) {
            WinAPI::TranslateMessage( &msg );
            WinAPI::DispatchMessage( &msg );
        }
        Finish( m_hWnd );

        return msg.wParam;

    }


    LRESULT MainWindow::OnMessage( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {

        static bool s_dragging = false;

        //各メッセージのhandlerを呼ぶ
        switch( msg ) {
        case WM_CREATE:
            Initialize( hwnd );
            SetupRegion( hwnd );
            m_pEngine->SetCandidateLimit( m_config.GetEngineInfo().CandidateMax() );
            m_pEngine->ClearContext();
            WinAPI::SetTimer( hwnd, 1, 100, NULL );
            return 0;
        case WM_TIMER: {
            auto now = WinAPI::GetTickCount();
            if( (m_config.OpaqueLimit()*1000) < (now - m_lastDrawTime) ) {
                Display( hwnd, DrawMode::TRAN );
                m_lastDrawTime = now;
            }
            return 0;
        }
        case WM_PAINT:
            Display( hwnd, DrawMode::KEEP );
            return 0;
        case WM_DESTROY:
            m_pEngine->ClearContext();
            m_pEngine->SaveDict(); // サーバに辞書セーブを指令
            m_pEngine->Disconnect();
            Finish( hwnd );
            WinAPI::PostQuitMessage( 0 );
            return 0;
        case WM_HOTKEY:
            //printf("Hotkey: param=%x\n",wParam);
            ProcessKey( hwnd, (int)wParam );
            return 0;
        case WM_NCLBUTTONDOWN: // 非クライアント領域のマウス
            break;
        case WM_NCLBUTTONUP:
            break;
        case WM_LBUTTONDOWN:
            // タイトルバー以外でウィンドウをドラッグする技
            // http://hp.vector.co.jp/authors/VA023539/tips/window/005.htm
            WinAPI::PostMessage( hwnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam );
            s_dragging = true;
            break;
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
            // タイトルバーをドラッグしてからマウスボタンを離した場合、
            // 何故かLBUTTONUPメッセージのかわりにMOUSEMOVEメッセージが出るので、
            // これを利用して、ウィンドウをドラッグした後でフォーカスがもとのウィンド
            // ウに戻るようにする。
            if( s_dragging ) {
                WinRestore();
                s_dragging = false;
            }
            break;
        case WM_NCHITTEST: // タスクバーかどうかの判定メッセージ
            // タイトルバーがないのでウィンドウのどこをクリックされても
            // キャプションにマウスポインタがあると誤魔化すことができる。
            // return HTCAPTION;
            break;
        case WM_RBUTTONDOWN:
            //■アプリケーション終了
            WinAPI::PostMessage( hwnd, WM_COMMAND, IDM_QUIT, 0 );
            break;
        case WM_SIZE:
            // アイコン化されたときはホットキーを完全に無効にする
            // Windowsのメッセージは http://yokohama.cool.ne.jp/chokuto/hsp/message/ を参照した
            if( wParam == 1 ) { // 最小化
                //Finish( hwnd );
                m_charHotKeys.Disable( hwnd );
                m_ctrlHotKeys.Disable( hwnd );
                m_emacsHotKeys.Disable( hwnd );
                m_pEngine->SaveDict(); // サーバに辞書セーブを指令
                WinAPI::KillTimer( hwnd, 1 );
            } else {
                UpdateMonitorInfo();
                m_charHotKeys.Enable( hwnd );
                m_ctrlHotKeys.Enable( hwnd );
                m_emacsHotKeys.Enable( hwnd );
                ResetConv( hwnd, false );
                //ResetText( hwnd );
                //Initialize( hwnd );
                WinAPI::SetTimer( hwnd, 1, 100, NULL );
            }
            break;
        case WM_COMMAND:
            switch( LOWORD( wParam ) ) {
            case IDM_ABOUT:
                WinAPI::MessageBox( hwnd,
                                    L"CLIME for Windows\n(C) 2024 project-enigma\n"
                                    L"based on works by (C)2001,2002 Toshiyuki Masui",
                                    L"About winclime", MB_OK );
                break;
            case IDM_QUIT:
                m_pEngine->ClearContext();
                m_pEngine->SaveDict(); // サーバに辞書セーブを指令
                m_pEngine->Disconnect();
                Finish( hwnd );
                WinAPI::KillTimer( hwnd, 1 );
                WinAPI::PostQuitMessage( 0 );
                break;
            }
        }

        return WinAPI::DefWindowProc( hwnd, msg, wParam, lParam );
    }

    void MainWindow::CalcWindowSize( int& width, int& height ) {
//
// MEMO : 現状のコードでもひとまず動作しているが、FontBold=true で少しフォントが「太る」
//        ため、実際のフォントを使って描画幅を取得しようとしたのが以下でコメントアウトされて
//        いるコード。残念ながら、このメンバ関数は CreateWindow 以前にコールされるため、
//        正常に動作しない。ひとまず諦めることにする。
//
//      SIZE size;
//      {
//          unsigned char buf[] = { 0x81, 0x41, 0x00 };
//          PAINTSTRUCT ps;
//          HDC hdc = WinAPI::BeginPaint( m_hWnd, &ps );
//          WinAPI::SelectObject( hdc, m_hFont );
//          WinAPI::GetTextExtentPoint32( hdc, (const char*)buf, 2, &size );
//          WinAPI::EndPaint( m_hWnd, &ps );
//      }
        width  = m_config.GetBezelWidth() +
            3 +
//          size.cx * m_config.GetBoxCharCount() +
            m_config.FontSize() * m_config.GetBoxCharCount() +
            3 +
            m_config.GetBezelWidth() + 1;
        height = m_config.GetDistance() +
            m_config.GetBezelWidth() +
            3 +
            m_config.FontSize() + 
            3 +
            m_config.GetInnerMargin() + 
            3 +
            m_config.FontSize() * m_config.GetListRowCount() +
            3 +
            m_config.GetBezelWidth() + 1;
    }

    void MainWindow::Initialize( HWND hwnd ) {
        m_baseHotKeys.Enable( hwnd );
        m_ctrlHotKeys.Enable( hwnd );
        m_emacsHotKeys.Enable( hwnd );
        m_charHotKeys.Enable( hwnd );
        ResetConv( hwnd );
        m_pTxtBox->Clear();
        UpdateMonitorInfo();
    }

    void MainWindow::Finish( HWND hwnd ) {
        m_charHotKeys.Disable( hwnd );
        m_ctrlHotKeys.Disable( hwnd );
        m_emacsHotKeys.Disable( hwnd );
        m_baseHotKeys.Disable( hwnd );
    }

    void MainWindow::RegisterWord() {
        wchar_t tmp1[256];
        wchar_t tmp2[256];
        wchar_t buf[1024];
        WinAPI::LoadString( m_hThisInstance, IDS_REGWORDDLG_PROMPT, tmp1, 256 );
        ::wsprintfW( tmp2, tmp1, m_inputs.c_str() );
        WinAPI::LoadString( m_hThisInstance, IDS_REGWORDDLG_TITLE,  tmp1, 256 );
        buf[0] = '\0';
        bool ret = DoInputBox( tmp1, tmp2, buf, 1024 );
        int len = ::wcslen( buf );
        if( ret && 0 < len ) {
            m_pTxtBox->Insert( buf );
            m_pEngine->RegWord( m_inputs.c_str(), buf );
            ResetConv( m_hWnd );
        }
    }

    void MainWindow::DeleteWord() {
        uint32_t sel = m_pCands->Selection();
        const wchar_t* pWord = (*m_pCands)[sel-1];
        m_pEngine->DelWord( pWord );
        Search( m_hWnd );
        while( m_pCands->Size() < sel )
            --sel;
        m_pCands->Selection() = sel;
    }

    void MainWindow::ResetConv( HWND /*hwnd*/, bool bEnable ) {
        m_pCands->Clear();
        m_inputs.clear();
        m_exactMatch = false;
        if( bEnable )
            m_bConverting = true;
    }

    void MainWindow::Search( HWND hwnd, bool bNext ) {
    #ifndef NDEBUG
        m_charHotKeys.Disable( m_hWnd );
        m_ctrlHotKeys.Disable( m_hWnd );
        m_emacsHotKeys.Disable( m_hWnd );
        m_baseHotKeys.Disable( m_hWnd );
    #endif // NDEBUG
        m_pCands->Clear();
        bool ret = false;
        auto func = [this]( const wchar_t* pTop, const wchar_t* pEnd ) -> bool {
                        if( pTop == pEnd )
                            m_pCands->NoMoreNext() = true;
                        else {
                            if( m_pCands->IsFull() )
                                return false;
                            m_pCands->Add( pTop, pEnd );
                        }
                        return true;
                    };
        if( !bNext )
            ret = m_pEngine->ExecSearch( m_inputs.c_str(), m_exactMatch, func );
        else
            ret = m_pEngine->ExecSearchNext( func );
        if( !ret ) {
            WinAPI::MessageBox( hwnd,
                                L"Can NOT interact with clime engine",
                                L"", MB_ICONEXCLAMATION | MB_OK );
            exit( 2 );
        }
    #ifndef NDEBUG
        m_baseHotKeys.Enable( m_hWnd );
        m_ctrlHotKeys.Enable( m_hWnd );
        m_emacsHotKeys.Enable( m_hWnd );
        m_charHotKeys.Enable( m_hWnd );
    #endif // NDEBUG
    }

    void MainWindow::SelectCandidate() {
        m_pTxtBox->Insert( **m_pCands );
        m_pEngine->NotifySelection( m_pCands->Selection() - 1 );    // 選択結果をサーバに通知
    }

    void MainWindow::ProcessKey( HWND hwnd, int keyCode ) {
        DrawMode mode = DrawMode::KEEP;
        auto& fnc = m_keyHandlers[keyCode];
        (this->*fnc)( hwnd, keyCode, mode );
        //ToDo：上記でコールされるハンドラの中でやっていることを整理し、以下に集約できる想定。
        //ToDo：（たとえば ctrl hot keys とかの制御など）
        RECT rect;
        WinAPI::GetClientRect( hwnd, &rect );
        WinAPI::InvalidateRect( hwnd, &rect, FALSE );
        Display( hwnd, mode );
    }

    bool MainWindow::InsertText() {

        bool result = true;
        const wchar_t* p;
        uint32_t sendMethod = SelectSendMethod( &p );

        // WM_CHAR/WM_UNICHAR での投入の場合
        if( SendMethod::IsWinMessage( sendMethod ) ) {
            uint32_t msecInterval = 0;
            uint32_t msgType = SendMethod::GetWinMessage( sendMethod, msecInterval );
            HWND wnd = WinSave();
            const wchar_t* pTop = m_pTxtBox->GetText();
            const wchar_t* pEnd = pTop + m_pTxtBox->Length();
            if( msgType == WM_CHAR ) {
                for( ; pTop < pEnd; ++pTop ) {
                    WinAPI::PostMessage( wnd, msgType, *pTop, 0 );
                    WinAPI::Sleep( msecInterval );
                }
            } else if( msgType == WM_UNICHAR ) {
                while( pTop < pEnd ) {
                    uint32_t codePoint = 0;
                    pTop = UTF16::GetCodePoint( pTop, codePoint );
                    WinAPI::PostMessage( wnd, msgType, codePoint, 0 );
                    WinAPI::Sleep( msecInterval );
                }
            }
            WinRestore();
//          if( p ) {
//              WinAPI::MessageBox( 0, p, L"", MB_ICONEXCLAMATION | MB_OK );
//          }

        // 上記以外であれば、クリップボード経由で指定されたキーバインドでの貼り付けを試行
        } else {
            if( !WinAPI::OpenClipboard( NULL ) )
                return false;
            if( !WinAPI::EmptyClipboard() ) {
                WinAPI::CloseClipboard();
                return false;
            }
            const wchar_t* pTop = m_pTxtBox->GetText();
            const wchar_t* pEnd = pTop + m_pTxtBox->Length();
            int byteLen = sizeof(wchar_t) * ((pEnd - pTop) + 1);
            HGLOBAL uniHandle = WinAPI::GlobalAlloc( GHND, byteLen ); {
                auto pBuf = reinterpret_cast<wchar_t*>( WinAPI::GlobalLock( uniHandle ) );
                std::copy( pTop, pEnd, pBuf );
                pBuf[pEnd - pTop] = 0;
                WinAPI::GlobalUnlock( uniHandle );
            }
            bool result = true;
            if( WinAPI::SetClipboardData( CF_UNICODETEXT, uniHandle ) == NULL ) {
                WinAPI::GlobalFree( uniHandle );
                result = false;
            }
            WinAPI::CloseClipboard();
            if( result ) {
                int32_t bucky1, bucky2, key;
                SendMethod::GetPastekey( sendMethod, bucky1, bucky2, key );
                SimulateKeyEvent( key, bucky1, bucky2 );
            }
        }
        if( result ) {
            const wchar_t* pTop = m_pTxtBox->GetText();
            const wchar_t* pEnd = pTop + m_pTxtBox->Length();
            m_lastResult = std::wstring{ pTop, pEnd };
        }
        return result;
    }

    void MainWindow::SetupRegion( HWND hwnd ) {
        RECT rect;
        WinAPI::GetClientRect( hwnd, &rect );
        m_rgnBelow = CreateBelowRegion( rect );
        m_rgnAbove = CreateAboveRegion( rect );
        if( GetPosition() == Position::BELOW )
            WinAPI::SetWindowRgn( hwnd, m_rgnBelow, TRUE );
        else
            WinAPI::SetWindowRgn( hwnd, m_rgnAbove, TRUE );
        WinAPI::SetLayeredWindowAttributes( hwnd, 0, 0xFF, LWA_ALPHA );
    }

    HRGN MainWindow::CreateBelowRegion( const RECT& rect ) {
        const int distance = m_config.GetDistance();
        const int offsetX  = m_config.GetWndOffsetX() * -1;

        // 吹き出し用丸矩形領域
        const int roundR = m_config.GetWndRoundR();
        HRGN hrgn1 = WinAPI::CreateRoundRectRgn( 0, distance, rect.right,
                                                 rect.bottom, roundR, roundR );
        // 吹き出し用三角領域
        POINT p[3];
        p[0].x = offsetX;
        p[0].y =  0;
        p[1].x = offsetX - 10;
        p[1].y = distance;
        p[2].x = offsetX + 10;
        p[2].y = distance;
        HRGN hrgn2 = WinAPI::CreatePolygonRgn( p, 3, WINDING );
        HRGN hrgn3 = WinAPI::CreateRectRgn( 0, 0, 1, 1 ); // ダミー
        WinAPI::CombineRgn( hrgn3, hrgn1, hrgn2, RGN_OR );
        return hrgn3;
    }

    HRGN MainWindow::CreateAboveRegion( const RECT& rect ) {
        const int distance = m_config.GetDistance();
        const int offsetX  = m_config.GetWndOffsetX() * -1;

        // 吹き出し用丸矩形領域
        const int roundR = m_config.GetWndRoundR();
        HRGN hrgn1 = WinAPI::CreateRoundRectRgn( 0, 0, rect.right,
                                                 rect.bottom - distance, roundR, roundR );
        // 吹き出し用三角領域
        POINT p[3];
        p[0].x = offsetX;
        p[0].y = rect.bottom;
        p[1].x = offsetX - 10;
        p[1].y = rect.bottom - distance - 1;
        p[2].x = offsetX + 10;
        p[2].y = rect.bottom - distance - 1;
        HRGN hrgn2 = WinAPI::CreatePolygonRgn( p, 3, WINDING );
        HRGN hrgn3 = WinAPI::CreateRectRgn( 0, 0, 1, 1 ); // ダミー
        WinAPI::CombineRgn( hrgn3, hrgn1, hrgn2, RGN_OR );
        return hrgn3;
    }

    void MainWindow::Display( HWND hwnd, DrawMode mode ) {

        if( mode == DrawMode::KEEP )
            mode = m_lastDrawMode;

        if( mode == DrawMode::TRAN )
            WinAPI::SetLayeredWindowAttributes( hwnd, 0, m_config.TransparentAlpha(), LWA_ALPHA );
        else {
            WinAPI::SetLayeredWindowAttributes( hwnd, 0, 0xFF, LWA_ALPHA );
            m_lastDrawTime = WinAPI::GetTickCount();
        }
        m_lastDrawMode = mode;

        //■描画開始
        PAINTSTRUCT ps;
        HDC hdc = WinAPI::BeginPaint( hwnd, &ps );

        WinAPI::SetBkMode( hdc, TRANSPARENT );

        //■フォントを設定
        /*HGDIOBJ tmp = */ WinAPI::SelectObject( hdc, m_hFont );

        RECT rct;
        WinAPI::GetClientRect( hwnd, &rct );
        WinAPI::FillRect( hdc, &rct, m_config.GetTheme().brshBezel );


        const wchar_t* pSelText = nullptr;
        int            selTextLen = 0;
        if( m_pCands->Selection() == 0 ) {
            pSelText = m_inputs.c_str();
            selTextLen = m_inputs.length();
        } else {
            auto i = m_pCands->Selection() - 1;
            pSelText = (*m_pCands)[i];
            selTextLen = m_pCands->LengthOf( i );
        }

        RECT buf;
        bool bBelow = (GetPosition() == Position::BELOW);
        const int candx = m_pTxtBox->DrawTextBox( hdc, m_config,
                                                  m_bConverting, pSelText, selTextLen,
                                                  m_config.GetTextBoxRect( buf, rct, bBelow ) );
        m_pLstBox->DrawListBox( hdc, m_config, m_bIndexing, candx,
                                *m_pCands, m_config.GetListBoxRect( buf, rct, bBelow ) );

        //■描画終了
        WinAPI::EndPaint( hwnd, &ps );

    }

    void MainWindow::OnEmptyKey( HWND /*hwnd*/, int /*keyCode*/, DrawMode& /*mode*/ ) {
        // intentionally do nothing...
    }

    void MainWindow::OnNormalKey( HWND hwnd, int keyCode, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) // (たぶん)最初の入力文字の場合はウィンドウ移動
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );

        if( !m_bConverting ) {
            wchar_t buf[2] = { (wchar_t)keyCode, 0 };
            m_pTxtBox->Insert( buf );
        } else {
            if( 0 < m_pCands->Selection() ) {
                SelectCandidate();
                ResetConv( hwnd );
            } else if( m_exactMatch ) {
                m_pCands->Selection() = 1;
                SelectCandidate();
                ResetConv( hwnd );
            }
            wchar_t buf[16];    //ToDo：１文字前提なら3バイトで十分だが‥‥‥どうする？
            if( m_inputs.empty() && m_bDirectKeying &&
                m_config.GetDirectKey( keyCode, buf ) == true ) {
                ResetConv( hwnd );
                m_pTxtBox->Insert( buf );
                m_pEngine->SetContext( buf );
                if( m_config.PredictAfterFix() )
                    Search( hwnd );
            } else {
                auto c = static_cast<unsigned char>( keyCode );
                m_inputs.push_back( c );
                Search( hwnd );
            }
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlJ( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( !m_bConverting )
            m_bConverting = true;
        else {
            if( 0 < m_pCands->Selection() )
                m_pTxtBox->Insert( **m_pCands );  //ToDo : SelectCandidate 呼び出しでなくて良いか？
            else
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
            m_bConverting = false;
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlA( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_A, 'A', MOD_CONTROL );
        } else if( m_inputs.empty() ) {
            m_pTxtBox->SetCaret( 0 );
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlB( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() || m_pTxtBox->GetCaret() == 0 ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_B, 'B', MOD_CONTROL );
        } else if( m_inputs.empty() ) {
            auto prevpos = m_pTxtBox->GetPrevPos();
            m_pTxtBox->SetCaret( prevpos );
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlD( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_D, 'D', MOD_CONTROL );
        } else if( m_inputs.empty() ) {
            m_pTxtBox->DeleteCaretChar();
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlE( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_E, 'E', MOD_CONTROL );
        } else if( m_inputs.empty() ) {
            m_pTxtBox->SetCaret( m_pTxtBox->Length() );
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlF( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        auto caret  = m_pTxtBox->GetCaret();
        auto length = m_pTxtBox->Length();
        if( m_pTxtBox->Empty() || caret == length ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_F, 'F', MOD_CONTROL );
        } else if( m_inputs.empty() && caret < length ) {
            auto nextpos = m_pTxtBox->GetNextPos();
            m_pTxtBox->SetCaret( nextpos );
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlK( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_K, 'K', MOD_CONTROL );
        } else if( m_inputs.empty() ) {
            m_pTxtBox->ChompAfterCaret();
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlG( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_bConverting ) {
            if( m_inputs.empty() == false )
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlQ( HWND /*hwnd*/, int /*keyCode*/, DrawMode& mode ) {
        if( 0 < m_pCands->Selection() ) {
            DeleteWord();
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlO( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_inputs.empty() == false ) {
            WinAPI::KillTimer( hwnd, 1 );
            RegisterWord();
            WinAPI::SetTimer( hwnd, 1, 100, NULL );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlT( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) {
            if( m_config.ForwardEmacsKey() )
                SimulateKeyEvent( hwnd, HOTKEY_CTRL_T, 'T', MOD_CONTROL );
        } else {
            m_pTxtBox->OperateCtrlT();
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnCtrlN( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( !(m_inputs.empty() && m_pCands->Empty()) ) {
            auto& idx = m_pCands->Selection();
            if( idx < m_pCands->Size() ) {
                idx += 1;
                mode = DrawMode::OPAQ;
                return;
            }
        }
        if( m_config.ForwardEmacsKey() )
            SimulateKeyEvent( hwnd, HOTKEY_CTRL_N, 'N', MOD_CONTROL );
    }

    void MainWindow::OnCtrlP( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( !(m_inputs.empty() && m_pCands->Empty()) ) {
            auto& idx = m_pCands->Selection();
            if( 0 < idx ) {
                idx -= 1;
                mode = DrawMode::OPAQ;
                return;
            }
        }
        if( m_config.ForwardEmacsKey() )
            SimulateKeyEvent( hwnd, HOTKEY_CTRL_P, 'P', MOD_CONTROL );
    }

    void MainWindow::OnAltQ( HWND hwnd, int /*keyCode*/, DrawMode& /*mode*/ ) {
        //■アプリケーション終了
        WinAPI::PostMessage( hwnd, WM_COMMAND, IDM_QUIT, 0 );
    }

    void MainWindow::OnAltJ( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        // アイコン化をトグルする。フォーカスを移動させると選択領域が
        // 変化してしまうので、前の選択領域を覚えておいてもとにもどす。
        // アイコン化したり開いたりしたときはWM_SIZEメッセージが
        // 出るので、そこでRegisterHotKeyの処理をする。
        if( WinAPI::IsIconic( hwnd ) ) {
            WinSave();
            OpenIcon( hwnd );
            WinRestore();
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
            mode = DrawMode::OPAQ;
        } else {
            WinSave();
            CloseWindow( hwnd );
            WinRestore();
        }
    }

    void MainWindow::OnAltW( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        (void)mode;
        std::wstring url = m_config.WebDictURL();
        // WebDictURL 設定文字列に ~A が含まれない場合はエラー終了
        auto pos = url.find( L"~A" );
        if( pos == std::wstring::npos ) {
        //ToDo : エラーメッセージを表示する？
            return;
        }
        wchar_t word[1024];
        word[0] = '\0';
        uint32_t sel = m_pCands->Selection();
        if( !!sel ) {
            //変換中で選択されている候補があればそれを使用
            const wchar_t* pWord = (*m_pCands)[sel-1];
            ::wcscpy( word, pWord );
        } else if( m_pTxtBox->Empty() == false ) {
            //上記以外で、入力途上の文字列があればそれを使用
            ::wcscpy( word, m_pTxtBox->GetText() );
        }
        /* InputBox で検索文字列を確定させる */ {
            wchar_t title[256];
            wchar_t prmpt[256];
            WinAPI::LoadString( m_hThisInstance, IDS_WEBDEFDLG_TITLE,  title, 256 );
            WinAPI::LoadString( m_hThisInstance, IDS_WEBDEFDLG_PROMPT, prmpt, 256 );
            bool ret = DoInputBox( title, prmpt, word, 1024 );
            int len = ::wcslen( word );
            if( ret && 0 < len )
                url.replace( pos, 2, word );
            else
                url.clear();
        }
        if( url.empty() == false )
            WinAPI::Shell_Execute( hwnd, L"open", url.c_str(), NULL, L".", SW_SHOW );
    }

    void MainWindow::OnBackSpaceKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        mode = DrawMode::OPAQ;
        //■候補選択中であればひとつ戻す
        if( 0 < m_pCands->Selection() )
            m_pCands->Selection() -= 1;
        //■完全に未入力の状態であればターゲットウィンドウにキーイベントを転送
        else if( m_inputs.empty() && m_pTxtBox->Empty() ) {
            SimulateKeyEvent( hwnd, HOTKEY_BACKSP, VK_BACK );
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
            mode = DrawMode::KEEP;
        //■未確定の入力はないがテキストボックスが空でない場合、カレット直前の１文字を削除
        } else if( m_inputs.empty() ) {
            m_pTxtBox->OperateBackspace();

        //■未確定の入力がある場合、１文字減らして再検索
        } else if( m_inputs.empty() == false ) {
            m_inputs.pop_back();
            if( m_inputs.empty() == false )
                Search( hwnd );
            else
                ResetConv( hwnd );
        }
    }

    void MainWindow::OnDeleteKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        //■完全に未入力の状態であればターゲットウィンドウにキーイベントを転送
        if( m_inputs.empty() && m_pTxtBox->Empty() ) {
            SimulateKeyEvent( hwnd, HOTKEY_DELETE, VK_DELETE );
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
            mode = DrawMode::KEEP;
        //■未確定の入力はないがテキストボックスが空でない場合、カレット直後の１文字を削除
        } else if( m_inputs.empty() ) {
            m_pTxtBox->DeleteCaretChar();
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnEscapeKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_bConverting ) {
            if( m_inputs.empty() == false )
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnSpaceKey( HWND /*hwnd*/, int /*keyCode*/, DrawMode& mode ) {
        if( m_inputs.empty() && m_pCands->Empty() )
            m_pTxtBox->Insert( L" " );
        else {
            auto& idx = m_pCands->Selection();
            if( idx < m_pCands->Size() ) {
                idx += 1;
                if( m_pCands->NoMoreNext() == false
                    && m_pCands->Size() < (idx + m_config.GetListRowCount()) ) {
                    auto backup = idx;
                    Search( m_hWnd, true );
                    idx = backup;
                }
            }
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnEnterKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        mode = DrawMode::OPAQ;
        if( 0 < m_pCands->Selection() ) {
            SelectCandidate();
            // SetCharHotkey(hwd,NOINPUT);
            ResetConv( hwnd );
            if( m_config.PredictAfterFix() )
                Search( hwnd );
        } else if( m_inputs.empty() ) {
            if( m_pTxtBox->Empty() ) {
                // 普通にリターンキーが押された状況を再現
                SimulateKeyEvent( hwnd, HOTKEY_RETURN, VK_RETURN );
                mode = DrawMode::KEEP;
            } else {
                InsertText();
                m_pTxtBox->Clear();
                ResetConv( hwnd );
                if( m_config.PredictAfterFix() )
                    Search( hwnd );
            }
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
        } else if( !m_exactMatch ){
            m_exactMatch = true;
            Search( hwnd );
        } else {
            m_pCands->Selection() = 1;
            SelectCandidate();
            ResetConv( hwnd );
        }
    }

    void MainWindow::OnCursorKey( HWND hwnd, int keyCode, DrawMode& mode ) {
        mode = DrawMode::OPAQ;
        int vkey = 0;
        switch( keyCode ) {
        case HOTKEY_LEFT:
            if( m_pTxtBox->Empty() == false &&
                           m_inputs.empty() && 0 < m_pTxtBox->GetCaret() ) {
                auto prevpos = m_pTxtBox->GetPrevPos();
                m_pTxtBox->SetCaret( prevpos );
                return;
            }
            vkey = VK_LEFT;
            break;
        case HOTKEY_UP:
            if( !(m_inputs.empty() && m_pCands->Empty()) ) {
                if( 0 < m_pCands->Selection() ) {
                    m_pCands->Selection() -= 1;
                    return;
                }
            }
            vkey = VK_UP;
            break;
        case HOTKEY_RIGHT:
            if( m_pTxtBox->Empty() == false && m_inputs.empty() && 
                           m_pTxtBox->GetCaret() < m_pTxtBox->Length() ) {
                auto nextpos = m_pTxtBox->GetNextPos();
                m_pTxtBox->SetCaret( nextpos );
                return;
            }
            vkey = VK_RIGHT;
            break;
        case HOTKEY_DOWN:
            if( !(m_inputs.empty() && m_pCands->Empty()) ) {
                if( m_pCands->Selection() < m_pCands->Size() ) {
                    m_pCands->Selection() += 1;
                    return;
                }
            }
            vkey = VK_DOWN;
            break;
        }
        //ここに到達した場合、ターゲットウィンドウにキー操作を転送
        mode = DrawMode::KEEP;
        SimulateKeyEvent( hwnd, keyCode, vkey );
        MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
    }

    void MainWindow::OnHomeKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() == false && m_inputs.empty() )
            OnCtrlA( hwnd, HOTKEY_CTRL_A, mode );
        else {
            mode = DrawMode::KEEP;
            SimulateKeyEvent( hwnd, HOTKEY_HOME, VK_HOME );
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
        }
    }

    void MainWindow::OnEndKey( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() == false && m_inputs.empty() )
            OnCtrlE( hwnd, HOTKEY_CTRL_E, mode );
        else {
            mode = DrawMode::KEEP;
            SimulateKeyEvent( hwnd, HOTKEY_END, VK_END );
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
        }
    }

    void MainWindow::OnCtrlSemicolon( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_bConverting ) {
            if( 0 < m_pCands->Selection() )
                SelectCandidate();
            else if( m_exactMatch ) {
                m_pCands->Selection() = 1;
                SelectCandidate();
            } else if( m_inputs.empty() == false )
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
            wchar_t buf[16]; {        // YYYY/MM/DD
                time_t now;
                tm     tm;
                ::time( &now );
                ::memcpy( &tm, ::localtime( &now ), sizeof(tm) );
                ::wsprintfW( buf, L"%04d/%02d/%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday );
            }
            m_inputs = buf;
            Search( hwnd );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlColon( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_bConverting ) {
            if( 0 < m_pCands->Selection() )
                SelectCandidate();
            else if( m_exactMatch ) {
                m_pCands->Selection() = 1;
                SelectCandidate();
            } else if( m_inputs.empty() == false )
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
            wchar_t buf[12]; {        // HH:MM:DD
                time_t now;
                tm     tm;
                ::time( &now );
                ::memcpy( &tm, ::localtime( &now ), sizeof(tm) );
                ::wsprintfW( buf, L"%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec );
            }
            m_inputs = buf;
            Search( hwnd );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlSpace( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_pTxtBox->Empty() ) // (たぶん)最初の入力文字の場合はウィンドウ移動
            MoveToCursor( hwnd, m_config, m_wndWidth, m_wndHeight );
        if( m_bConverting ) {
            if( 0 < m_pCands->Selection() )
                SelectCandidate();
            else if( m_exactMatch ) {
                m_pCands->Selection() = 1;
                SelectCandidate();
            } else if( m_inputs.empty() == false )
                m_pTxtBox->Insert( m_inputs.c_str() );
            ResetConv( hwnd );
        }
        m_pTxtBox->Insert( L" " );
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnCtrlNumber( HWND hwnd, int keyCode, DrawMode& mode ) {
        uint32_t number = keyCode - HOTKEY_CTRL_0;
        OnNormalKey( hwnd, '0' + number, mode );
    }

    void MainWindow::OnNumber( HWND hwnd, int keyCode, DrawMode& mode ) {
        uint32_t number = keyCode - HOTKEY_NUM_1 + 1;
        if( m_pCands->Empty() || m_bIndexing == false )
            OnNormalKey( hwnd, '0' + number, mode );
        else {
            number += m_pCands->Selection();
            if( number <= m_pCands->Size() ) {
                m_pCands->Selection() = number;
                SelectCandidate();
                ResetConv( hwnd );
                if( m_config.PredictAfterFix() )
                    Search( hwnd );
            }
            mode = DrawMode::OPAQ;
        }
    }

    void MainWindow::OnNextTheme( HWND /*hwnd*/, int /*keyCode*/, DrawMode& mode ) {
        m_config.NextTheme();
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnHelpKey( HWND hwnd, int /*keyCode*/, DrawMode& /*mode*/ ) {
        const wchar_t* pPageName = m_helpPath.c_str();
        int32_t ret = WinAPI::GetFileAttributes( pPageName );
        if( 0 <= ret )
            WinAPI::Shell_Execute( hwnd, L"open", pPageName, NULL, L".", SW_SHOW );
        else {
            wchar_t fmt[256];
            wchar_t buf[256];
            WinAPI::LoadString( m_hThisInstance, IDS_ERRMSG_MANUAL_MISSING, fmt, 256 );
            ::wsprintfW( buf, fmt, pPageName );
            m_charHotKeys.Disable( m_hWnd );
            m_ctrlHotKeys.Disable( m_hWnd );
            m_emacsHotKeys.Disable( m_hWnd );
            m_baseHotKeys.Disable( m_hWnd );
            WinSave();
            WinAPI::MessageBox( hwnd, buf, clime::APPNAME, MB_ICONERROR | MB_OK );
            WinRestore();
            m_baseHotKeys.Enable( m_hWnd );
            m_ctrlHotKeys.Enable( m_hWnd );
            m_emacsHotKeys.Enable( m_hWnd );
            m_charHotKeys.Enable( m_hWnd );
        }
    }

    void MainWindow::OnVersionKey( HWND hwnd, int /*keyCode*/, DrawMode& /*mode*/ ) {
        wchar_t engVersion[32];
        m_pEngine->GetVersion( [&engVersion]( const wchar_t* pTop, const wchar_t* pEnd ) -> bool {
                                   auto len = pEnd - pTop;
                                   ::wcsncpy( engVersion, pTop, len );
                                   engVersion[len] = 0;
                                   return true;
                               } );
        wchar_t title[256];
        wchar_t format[256];
        wchar_t msg[256];
        WinAPI::LoadString( m_hThisInstance, IDS_MSG_VERSION_TITLE,  title,  256 );
        WinAPI::LoadString( m_hThisInstance, IDS_MSG_VERSION_FORMAT, format, 256 );
        ::wsprintfW( msg, format, WINCLIME_MAJOR_VER, WINCLIME_MINOR_VER, engVersion );
        m_charHotKeys.Disable( m_hWnd );
        m_ctrlHotKeys.Disable( m_hWnd );
        m_emacsHotKeys.Disable( m_hWnd );
        m_baseHotKeys.Disable( m_hWnd );
        WinSave();
        WinAPI::MessageBox( hwnd, msg, title, MB_ICONINFORMATION | MB_OK );
        WinRestore();
        m_baseHotKeys.Enable( m_hWnd );
        m_ctrlHotKeys.Enable( m_hWnd );
        m_emacsHotKeys.Enable( m_hWnd );
        m_charHotKeys.Enable( m_hWnd );
    }

    void MainWindow::OnRecallResult( HWND hwnd, int /*keyCode*/, DrawMode& mode ) {
        if( m_lastResult.empty() == false && m_pTxtBox->Empty() == true ) {
            if( m_bConverting )
                ResetConv( hwnd );
            m_pTxtBox->Clear();
            m_pTxtBox->Insert( m_lastResult.c_str() );
        }
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnToggleIndexing( HWND /*hwnd*/, int /*keyCode*/, DrawMode& mode ) {
        m_bIndexing = !m_bIndexing;
        mode = DrawMode::OPAQ;
    }

    void MainWindow::OnToggleDirectKey( HWND /*hwnd*/, int /*keyCode*/, DrawMode& mode ) {
        m_bDirectKeying = !m_bDirectKeying;
        mode = DrawMode::OPAQ;
    }

    const wchar_t* MainWindow::GetTargetImageName( HWND hWnd ) {
        static wchar_t s_imageName[4096];
        DWORD processID;
        WinAPI::GetWindowThreadProcessId( hWnd, &processID );
        HANDLE hProcess = WinAPI::OpenProcess( PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID );
        const wchar_t* p = s_imageName;
        if( hProcess ) {
            DWORD size = 4096;  // BAD-IDEA.
            WinAPI::QueryFullProcessImageNameW( hProcess, 0, s_imageName, &size );
            WinAPI::CloseHandle( hProcess );
            for( uint32_t i = 0; i < size; ++i ) {
                if( s_imageName[i] == L'\\' )
                    p = s_imageName + i + 1;
            }
        }
        return p;
    }

    uint32_t MainWindow::SelectSendMethod( const wchar_t** ppExeName ) {

        static HWND     s_lastTargetWnd    = 0;
        static uint32_t s_lastSelectMethod = 0;

        if( ppExeName )
            *ppExeName = nullptr;

        HWND targetWnd = WinAPI::GetForegroundWindow();
        if( targetWnd == s_lastTargetWnd )
            return s_lastSelectMethod;

        const wchar_t* pExeName = GetTargetImageName( targetWnd );
        uint32_t sendMethod = 0;
        m_config.GetSendMethod( pExeName, sendMethod );

        if( ppExeName )
            *ppExeName = pExeName;

        s_lastTargetWnd    = targetWnd;
        s_lastSelectMethod = sendMethod;
        return sendMethod;
    }

    void MainWindow::SimulateKeyEvent( int key, int bucky1, int bucky2 ) {
        if( !!bucky1 ) {
            keybd_event( bucky1, (BYTE)MapVirtualKey(bucky1,0), 0, 0);
            WinAPI::Sleep( m_config.SleepTime() );
        }
        if( !!bucky2 ) {
            keybd_event( bucky2, (BYTE)MapVirtualKey(bucky2,0), 0, 0);
            WinAPI::Sleep( m_config.SleepTime() );
        }
        keybd_event( key, (BYTE)MapVirtualKey(key,0), 0, 0 );
        WinAPI::Sleep( m_config.SleepTime() );
        keybd_event( key, (BYTE)MapVirtualKey(key,0), KEYEVENTF_KEYUP, 0 );
        if( !!bucky2 )
            keybd_event( bucky2, (BYTE)MapVirtualKey(bucky2,0), KEYEVENTF_KEYUP, 0 );
        if( !!bucky1 )
            keybd_event( bucky1, (BYTE)MapVirtualKey(bucky1,0), KEYEVENTF_KEYUP, 0 );
    }

    void MainWindow::SimulateKeyEvent( HWND hwnd, int hotKey, int key, int bucky ) {
        WinAPI::UnregisterHotKey( hwnd, hotKey );
        SimulateKeyEvent( key, bucky, 0 );
        WinAPI::RegisterHotKey( hwnd, hotKey, bucky, key );
    }

    void MainWindow::OnChangePosition( HWND hwnd, WindowMover::Position pos ) {
        HRGN rgnPrev = WinAPI::CreateRectRgn(0,0,0,0);
        WinAPI::GetWindowRgn( hwnd, rgnPrev );
        if( pos == Position::BELOW ) {
            WinAPI::SetWindowRgn( hwnd, m_rgnBelow, TRUE );
            m_rgnAbove = rgnPrev;
        } else {
            WinAPI::SetWindowRgn( hwnd, m_rgnAbove, TRUE );
            m_rgnBelow = rgnPrev;
        }
    }

    void MainWindow::RegisterHotKeys() {

        // base hot keys -------------------------------------------------------
        m_baseHotKeys.AddKey( HOTKEY_ALT_J, MOD_ALT, 'J'   );  // ALT-J でon/off

        // ctrl hot keys -------------------------------------------------------
        m_ctrlHotKeys.AddKey( HOTKEY_CTRL_C, MOD_CONTROL, 'C' ); // Ctrl-C
        m_ctrlHotKeys.AddKey( HOTKEY_CTRL_J, MOD_CONTROL, 'J' ); // Ctrl-J
        m_ctrlHotKeys.AddKey( HOTKEY_CTRL_Q, MOD_CONTROL, 'Q' ); // Ctrl-Q
        m_ctrlHotKeys.AddKey( HOTKEY_CTRL_O, MOD_CONTROL, 'O' ); // Ctrl-O
        m_ctrlHotKeys.AddKey( HOTKEY_ALT_Q,  MOD_ALT,     'Q' ); // ALT-Q で終了
        m_ctrlHotKeys.AddKey( HOTKEY_ALT_D,  MOD_ALT,     'D' ); // ALT-D でダイレクトキー機能トグル
        m_ctrlHotKeys.AddKey( HOTKEY_ALT_W,  MOD_ALT,     'W' ); // ALT-W で Web 辞書連携
        m_ctrlHotKeys.AddKey( HOTKEY_CTRL_I, MOD_CONTROL, 'I' ); // Ctrl-I でインデックス機能トグル
//      m_ctrlHotKeys.AddKey( HOTKEY_CPSLCK, 0,    VK_CAPITAL ); // CAPS Lockでon/off
        m_ctrlHotKeys.AddKey( HOTKEY_RETURN, 0,     VK_RETURN ); // Return
        m_ctrlHotKeys.AddKey( HOTKEY_DELETE, 0,     VK_DELETE ); // DEL
        m_ctrlHotKeys.AddKey( HOTKEY_BACKSP, 0,       VK_BACK ); // BS
        m_ctrlHotKeys.AddKey( HOTKEY_ESCAPE, 0,     VK_ESCAPE ); // Esc
        m_ctrlHotKeys.AddKey( HOTKEY_LEFT,   0,       VK_LEFT );
        m_ctrlHotKeys.AddKey( HOTKEY_UP,     0,         VK_UP );
        m_ctrlHotKeys.AddKey( HOTKEY_RIGHT,  0,      VK_RIGHT );
        m_ctrlHotKeys.AddKey( HOTKEY_DOWN,   0,       VK_DOWN );
        m_ctrlHotKeys.AddKey( HOTKEY_HOME,   0,       VK_HOME );
        m_ctrlHotKeys.AddKey( HOTKEY_END,    0,        VK_END );

        // emacs hot keys ------------------------------------------------------
        if( m_config.EmacsKeyBind() ) {
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_A, MOD_CONTROL, 'A' ); // Ctrl-A
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_B, MOD_CONTROL, 'B' ); // Ctrl-B
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_D, MOD_CONTROL, 'D' ); // Ctrl-D
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_E, MOD_CONTROL, 'E' ); // Ctrl-E
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_F, MOD_CONTROL, 'F' ); // Ctrl-F
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_G, MOD_CONTROL, 'G' ); // Ctrl-G
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_K, MOD_CONTROL, 'K' ); // Ctrl-K
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_N, MOD_CONTROL, 'N' ); // Ctrl-N
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_P, MOD_CONTROL, 'P' ); // Ctrl-P
            m_emacsHotKeys.AddKey( HOTKEY_CTRL_T, MOD_CONTROL, 'T' ); // Ctrl-T
        }

        // char hot keys -------------------------------------------------------
        if( m_config.KeyboardType() == KbdType::KB_101 ) {
            m_charHotKeys.AddKey( HOTKEY_CTRL_SEMICOLON,         MOD_CONTROL, 0xBA ); // Ctrl-;
            m_charHotKeys.AddKey( HOTKEY_CTRL_COLON, MOD_SHIFT | MOD_CONTROL, 0xBA ); // Ctrl-:
        } else {
            m_charHotKeys.AddKey( HOTKEY_CTRL_SEMICOLON,         MOD_CONTROL, 0xBB ); // Ctrl-;
            m_charHotKeys.AddKey( HOTKEY_CTRL_COLON,             MOD_CONTROL, 0xBA ); // Ctrl-:
        }
        m_charHotKeys.AddKey( HOTKEY_CTRL_SPACE, MOD_CONTROL, VK_SPACE );
        m_charHotKeys.AddKey( HOTKEY_SPACE,      0,           VK_SPACE );
        m_charHotKeys.AddKey( HOTKEY_F01,        0,           VK_F1    );
        m_charHotKeys.AddKey( HOTKEY_F09,        0,           VK_F9    );
        m_charHotKeys.AddKey( HOTKEY_ALT_F01,    MOD_ALT,     VK_F1    );
        m_charHotKeys.AddKey( HOTKEY_ALT_F12,    MOD_ALT,     VK_F12   );

        for( int code = 'A'; code <= 'Z'; ++code )
            m_charHotKeys.AddKey( code+0x20, 0, code );
        for( int code = 'A'; code <= 'Z'; ++code )
            m_charHotKeys.AddKey( code, MOD_SHIFT, code );

        for( int idx = 0; idx <= 9; ++idx )
            m_charHotKeys.AddKey( HOTKEY_CTRL_0 + idx, MOD_CONTROL, '0' + idx );

        m_charHotKeys.AddKey( '0', 0, '0');
        for( int idx = 0; idx < 9; ++idx )
            m_charHotKeys.AddKey( HOTKEY_NUM_1 + idx, 0, '1' + idx );

        switch( m_config.KeyboardType() ) {
        case KbdType::KB_101:
            m_charHotKeys.AddKey( 0x21, MOD_SHIFT, 0x31 ); // !
            m_charHotKeys.AddKey( 0x40, MOD_SHIFT, 0x32 ); // @
            m_charHotKeys.AddKey( 0x23, MOD_SHIFT, 0x33 ); // #
            m_charHotKeys.AddKey( 0x24, MOD_SHIFT, 0x34 ); // $
            m_charHotKeys.AddKey( 0x25, MOD_SHIFT, 0x35 ); // %
            m_charHotKeys.AddKey( 0x5E, MOD_SHIFT, 0x36 ); // ^
            m_charHotKeys.AddKey( 0x26, MOD_SHIFT, 0x37 ); // &
            m_charHotKeys.AddKey( 0x2A, MOD_SHIFT, 0x38 ); // *
            m_charHotKeys.AddKey( 0x28, MOD_SHIFT, 0x39 ); // (
            m_charHotKeys.AddKey( 0x29, MOD_SHIFT, 0x30 ); // )
            m_charHotKeys.AddKey( 0x3A, MOD_SHIFT, 0xBA ); // :
            m_charHotKeys.AddKey( 0x3B, 0,         0xBA ); // ;
            m_charHotKeys.AddKey( 0x3D, 0,         0xBB ); // =
            m_charHotKeys.AddKey( 0x2B, MOD_SHIFT, 0xBB ); // +
            m_charHotKeys.AddKey( 0x2C, 0,         0xBC ); // ,
            m_charHotKeys.AddKey( 0x3C, MOD_SHIFT, 0xBC ); // <
            m_charHotKeys.AddKey( 0x2D, 0,         0xBD ); // -
            m_charHotKeys.AddKey( 0x5F, MOD_SHIFT, 0xBD ); // _
            m_charHotKeys.AddKey( 0x2E, 0,         0xBE ); // .
            m_charHotKeys.AddKey( 0x3E, MOD_SHIFT, 0xBE ); // >
            m_charHotKeys.AddKey( 0x2F, 0,         0xBF ); // /
            m_charHotKeys.AddKey( 0x3F, MOD_SHIFT, 0xBF ); // ?
            m_charHotKeys.AddKey( 0x60, 0,         0xC0 ); // `
            m_charHotKeys.AddKey( 0x7E, MOD_SHIFT, 0xC0 ); // ~
            m_charHotKeys.AddKey( 0x5D, 0,         0xDD ); // ]
            m_charHotKeys.AddKey( 0x7D, MOD_SHIFT, 0xDD ); // }
            m_charHotKeys.AddKey( 0x5C, 0,         0xDC ); // <backslash>
            m_charHotKeys.AddKey( 0x7C, MOD_SHIFT, 0xDC ); // |
            m_charHotKeys.AddKey( 0x5B, 0,         0xDB ); // [
            m_charHotKeys.AddKey( 0x7B, MOD_SHIFT, 0xDB ); // {
            m_charHotKeys.AddKey( 0x27, 0,         0xDE ); // '
            m_charHotKeys.AddKey( 0x22, MOD_SHIFT, 0xDE ); // "
            break;
        case KbdType::KB_106:
            m_charHotKeys.AddKey( 0x21, MOD_SHIFT, 0x31 ); // !
            m_charHotKeys.AddKey( 0x22, MOD_SHIFT, 0x32 ); // "
            m_charHotKeys.AddKey( 0x23, MOD_SHIFT, 0x33 ); // #
            m_charHotKeys.AddKey( 0x24, MOD_SHIFT, 0x34 ); // $
            m_charHotKeys.AddKey( 0x25, MOD_SHIFT, 0x35 ); // %
            m_charHotKeys.AddKey( 0x26, MOD_SHIFT, 0x36 ); // &
            m_charHotKeys.AddKey( 0x27, MOD_SHIFT, 0x37 ); // '
            m_charHotKeys.AddKey( 0x28, MOD_SHIFT, 0x38 ); // (
            m_charHotKeys.AddKey( 0x29, MOD_SHIFT, 0x39 ); // )
            m_charHotKeys.AddKey( 0x2A, MOD_SHIFT, 0xBA ); // *
            m_charHotKeys.AddKey( 0x2B, MOD_SHIFT, 0xBB ); // +
            m_charHotKeys.AddKey( 0x2C, 0,         0xBC ); // ,
            m_charHotKeys.AddKey( 0x2D, 0,         0xBD ); // -
            m_charHotKeys.AddKey( 0x2E, 0,         0xBE ); // .
            m_charHotKeys.AddKey( 0x2F, 0,         0xBF ); // /
            m_charHotKeys.AddKey( 0x3A, 0,         0xBA ); // :
            m_charHotKeys.AddKey( 0x3B, 0,         0xBB ); // ;
            m_charHotKeys.AddKey( 0x3C, MOD_SHIFT, 0xBC ); // <
            m_charHotKeys.AddKey( 0x3D, MOD_SHIFT, 0xBD ); // =
            m_charHotKeys.AddKey( 0x3E, MOD_SHIFT, 0xBE ); // >
            m_charHotKeys.AddKey( 0x3F, MOD_SHIFT, 0xBF ); // ?
            m_charHotKeys.AddKey( 0x40, 0,         0xC0 ); // @
            m_charHotKeys.AddKey( 0x5B, 0,         0xDB ); // [
            m_charHotKeys.AddKey( 0x5C, 0,         0xDC ); // <backslash>
            m_charHotKeys.AddKey( 0x5D, 0,         0xDD ); // ]
            m_charHotKeys.AddKey( 0x5E, 0,         0xDE ); // ^
            m_charHotKeys.AddKey( 0x5F, MOD_SHIFT, 0xE2 ); // _
            m_charHotKeys.AddKey( 0x60, MOD_SHIFT, 0xC0 ); // `
            m_charHotKeys.AddKey( 0x7B, MOD_SHIFT, 0xDB ); // {
            m_charHotKeys.AddKey( 0x7C, MOD_SHIFT, 0xDC ); // |
            m_charHotKeys.AddKey( 0x7D, MOD_SHIFT, 0xDD ); // }
            m_charHotKeys.AddKey( 0x7E, MOD_SHIFT, 0xDE ); // ~
            break;
        }
    }

    bool MainWindow::DoInputBox( const wchar_t* pTitle,
                                 const wchar_t* pPrompt, wchar_t* pBuf, uint32_t bufLen ) {
        m_charHotKeys.Disable( m_hWnd );
        m_ctrlHotKeys.Disable( m_hWnd );
        m_emacsHotKeys.Disable( m_hWnd );
        m_baseHotKeys.Disable( m_hWnd );
        InputBox inbox{ m_hThisInstance, m_hWnd };
        WinSave();
        bool ret = inbox.DoModal( pTitle, pPrompt, pBuf, bufLen );
        WinRestore();
        m_baseHotKeys.Enable( m_hWnd );
        m_ctrlHotKeys.Enable( m_hWnd );
        m_emacsHotKeys.Enable( m_hWnd );
        m_charHotKeys.Enable( m_hWnd );
        return ret;
    }
}
