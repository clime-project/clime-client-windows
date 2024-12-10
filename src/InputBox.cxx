//------------------------------------------------------------------------------
//
// InputBox.cxx
//
//------------------------------------------------------------------------------
#include "InputBox.hxx"

namespace clime {

    static constexpr const wchar_t* IB_CLASS_NAME   = L"InputBox558";
    static constexpr int            IB_SPAN         = 10;
    static constexpr int            IB_LEFT_OFFSET  = 10;
    static constexpr int            IB_TOP_OFFSET   = 10;
    static constexpr int            IB_WIDTH        = 300;
    static constexpr int            IB_HEIGHT       = 130;
    static constexpr int            IB_BTN_WIDTH    = 70;
    static constexpr int            IB_BTN_HEIGHT   = 24;


    InputBox::InputBox( HINSTANCE hInstance, HWND wndParent ) : m_hThisInstance( hInstance ),
                                                                m_wndParent( wndParent ),
                                                                m_wndThis( 0 ),
                                                                m_wndPrompt( 0 ),
                                                                m_wndEditBox( 0 ),
                                                                m_wndOKButton( 0 ),
                                                                m_wndCancelButton( 0 ),
                                                                m_pBuffer( nullptr ),
                                                                m_bufSize( 0 ),
                                                                m_bResult( false ) {

        WNDCLASSEXW wndInputBox;

        ::memset( &wndInputBox, 0, sizeof(wndInputBox) );

        wndInputBox.cbSize         = sizeof(wndInputBox);
        wndInputBox.lpszClassName  = IB_CLASS_NAME;
        wndInputBox.style          = CS_HREDRAW | CS_VREDRAW;
        wndInputBox.lpfnWndProc    = WndProc;
        wndInputBox.lpszMenuName   = NULL;
        wndInputBox.hIconSm        = NULL;
        wndInputBox.cbClsExtra     = 0;
        wndInputBox.cbWndExtra     = sizeof(InputBox*);
        wndInputBox.hInstance      = hInstance;
        wndInputBox.hIcon          = WinAPI::LoadIcon( NULL, IDI_WINLOGO );
        wndInputBox.hCursor        = WinAPI::LoadCursor( NULL, IDC_ARROW );
        wndInputBox.hbrBackground  = (HBRUSH)(COLOR_WINDOW);

        WinAPI::RegisterClass_Ex( &wndInputBox );

        RECT rect;
        if( m_wndParent )
            WinAPI::GetWindowRect( m_wndParent, &rect );
        else
            WinAPI::GetWindowRect( ::GetDesktopWindow(), &rect );

        m_wndThis = WinAPI::Create_Window( IB_CLASS_NAME, L"",
                                           (WS_BORDER | WS_CAPTION),
                                           rect.left+(rect.right-rect.left-IB_WIDTH)/2,
                                           rect.top+(rect.bottom-rect.top-IB_HEIGHT)/2,
                                           IB_WIDTH, IB_HEIGHT,
                                           m_wndParent, NULL, m_hThisInstance, this );
    }

    InputBox::~InputBox() {
        WinAPI::UnregisterClass( IB_CLASS_NAME, m_hThisInstance );
    }


    LRESULT CALLBACK InputBox::WndProc( HWND hWnd, UINT msg,
                                        WPARAM wParam, LPARAM lParam ) {
        InputBox* pInputBox = (InputBox*)WinAPI::GetWindowLongPtr( hWnd, 0 );
        if( msg == WM_CREATE ) {
            pInputBox = reinterpret_cast<InputBox*>( ((CREATESTRUCT*)lParam)->lpCreateParams );
            WinAPI::SetWindowLongPtr( hWnd, 0, (LONG_PTR)pInputBox );
        }
        return pInputBox->OnMessage( hWnd, msg, wParam, lParam );
    }


    bool InputBox::DoModal( LPCWSTR pTitle,
                            LPCWSTR pPrompt, LPWSTR pBuf, WORD bufLen ) {
        MSG msg;
        BOOL bRet;
        m_pBuffer = pBuf;
        m_bufSize = bufLen;
        m_bResult = false;

    //  EnableWindow(hwndParent, false);

        this->Show( pTitle, pPrompt );

        while( (bRet = WinAPI::GetMessage( &msg, NULL, 0, 0 ) ) != 0 ) {
            if( msg.message == WM_KEYDOWN ) {
                switch (msg.wParam) {
                case VK_RETURN: this->OnOK();
                    break;
                case VK_ESCAPE: this->OnCancel();
                    break;
                default:        ::TranslateMessage(&msg);
                    break;
                }
            } else
            //  if (!IsDialogMessage(hwndInputBox, &msg)) {
                    ::TranslateMessage( &msg );
            //  }
            ::DispatchMessage( &msg );
            if( msg.message == WM_CLOSE )
                break;
        }

    //  EnableWindow(hwndParent, true);

        return m_bResult;
    }

    LRESULT InputBox::OnMessage( HWND hWnd, UINT msg,
                                 WPARAM wParam, LPARAM lParam ) {
        switch( msg ) {
        case WM_CREATE:
            OnCreate( hWnd );
            break;
        case WM_COMMAND:
            switch( LOWORD( wParam ) ) {
            case IDOK:     OnOK();
                break;
            case IDCANCEL: OnCancel();
                break;
            }
            break;
        case WM_CLOSE:
            Hide();
            return 0;
        case WM_DESTROY:
            OnDestroy();
            break;
        }
        return WinAPI::DefWindowProc( hWnd, msg, wParam, lParam );
    }

    void InputBox::OnCreate( HWND hwndNew ) {

        m_wndThis = hwndNew;

    //  SetWindowPos(hwndInputBox, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        m_wndPrompt = WinAPI::Create_Window( L"Static", L"", WS_CHILD | WS_VISIBLE,
                                             IB_LEFT_OFFSET, IB_TOP_OFFSET,
                                             IB_WIDTH-IB_LEFT_OFFSET*2, IB_BTN_HEIGHT,
                                             m_wndThis, NULL, m_hThisInstance, NULL );
        m_wndEditBox = WinAPI::Create_Window( L"Edit", L"",
                                              WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
                                              IB_LEFT_OFFSET, IB_TOP_OFFSET + IB_BTN_HEIGHT,
                                              IB_WIDTH-IB_LEFT_OFFSET*3, IB_BTN_HEIGHT - 4,
                                              m_wndThis, NULL, m_hThisInstance, NULL );
        auto btnX = IB_WIDTH  - IB_BTN_WIDTH  - 15;
        auto btnY = IB_HEIGHT - IB_BTN_HEIGHT - 35;
        m_wndOKButton = WinAPI::Create_Window( L"Button", L"OK",
                                               WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                                               btnX, btnY, IB_BTN_WIDTH, IB_BTN_HEIGHT,
                                               m_wndThis, (HMENU)IDOK, m_hThisInstance, NULL );
        m_wndCancelButton = WinAPI::Create_Window( L"Button", L"Cancel",
                                                   WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                                                   btnX - IB_BTN_WIDTH - IB_SPAN, btnY,
                                                   IB_BTN_WIDTH, IB_BTN_HEIGHT,
                                                   m_wndThis, (HMENU)IDCANCEL, m_hThisInstance, NULL );

        auto myFont = (HFONT)WinAPI::GetStockObject( DEFAULT_GUI_FONT );

    //  WinAPI::SendMessage( m_wndThis,         WM_SETFONT, (WPARAM)myFont, FALSE );
        WinAPI::SendMessage( m_wndPrompt,       WM_SETFONT, (WPARAM)myFont, FALSE );
        WinAPI::SendMessage( m_wndEditBox,      WM_SETFONT, (WPARAM)myFont, FALSE );
        WinAPI::SendMessage( m_wndOKButton,     WM_SETFONT, (WPARAM)myFont, FALSE );
        WinAPI::SendMessage( m_wndCancelButton, WM_SETFONT, (WPARAM)myFont, FALSE );
    }

    void InputBox::Show( LPCWSTR pTitle, LPCWSTR pPrompt ) {
        WinAPI::SetWindowText( m_wndThis, pTitle );
        WinAPI::SetWindowText( m_wndEditBox, m_pBuffer );
        WinAPI::SetWindowText( m_wndPrompt, pPrompt );
        WinAPI::SendMessage( m_wndEditBox, EM_LIMITTEXT, m_bufSize, 0 );
        WinAPI::SendMessage( m_wndEditBox, EM_SETSEL, 0, -1 );
        WinAPI::SetFocus( m_wndEditBox );
        WinAPI::ShowWindow( m_wndThis, SW_NORMAL );
    }

    void InputBox::Hide() {
        WinAPI::ShowWindow( m_wndThis, SW_HIDE );
    }

    void InputBox::OnOK() {
        WORD length = (int)WinAPI::SendMessage( m_wndEditBox, EM_LINELENGTH, 0, 0 );
        if( length ) {
            *((LPWORD)m_pBuffer) = m_bufSize;
            length = (WORD)WinAPI::SendMessage( m_wndEditBox,
                                                EM_GETLINE, 0, (LPARAM)m_pBuffer );
        }
        m_pBuffer[length] = '\0';
        m_bResult = true;
        WinAPI::PostMessage( m_wndThis, WM_CLOSE, 0, 0 );
    }


    void InputBox::OnCancel() {
        WinAPI::PostMessage( m_wndThis, WM_CLOSE, 0, 0 );
    }

    void InputBox::OnDestroy() {
        WinAPI::EnableWindow( m_wndParent, true );
        WinAPI::SendMessage( m_wndThis, WM_DESTROY, 0, 0 );
    }

} // namespace clime
