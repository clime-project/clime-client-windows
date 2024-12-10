//------------------------------------------------------------------------------
//
// InputBox.hxx
//
//------------------------------------------------------------------------------
#ifndef INPUTBOX_HXX__
#define INPUTBOX_HXX__

#include "WinAPI.hxx"

namespace clime {

    class InputBox {
    public:
        InputBox( HINSTANCE hInstance, HWND wndParent );
        ~InputBox();

    private:
        static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg,
                                         WPARAM wParam, LPARAM lParam );

    public:
        bool DoModal( LPCWSTR pTitle,
                      LPCWSTR pPrompt,
                      LPWSTR pBuf, WORD bufLen );
        LRESULT OnMessage( HWND hWnd, UINT msg,
                           WPARAM wParam, LPARAM lParam );

    private:
        void OnCreate( HWND hwndNew );
        void Show( LPCWSTR lpszTitle, LPCWSTR lpszQuery );
        void Hide();
        void OnOK();
        void OnCancel();
        void OnDestroy();

    private:
        const HINSTANCE m_hThisInstance;
        const HWND      m_wndParent;
        HWND            m_wndThis;
        HWND            m_wndPrompt;
        HWND            m_wndEditBox;
        HWND            m_wndOKButton;
        HWND            m_wndCancelButton;
        LPWSTR          m_pBuffer;
        WORD            m_bufSize;
        bool            m_bResult;
    };

} // namespace clime

#endif // INPUTBOX_HXX__
