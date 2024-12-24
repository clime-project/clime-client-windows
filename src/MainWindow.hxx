//------------------------------------------------------------------------------
//
// MainWindow.hxx
//
//------------------------------------------------------------------------------
#ifndef MAINWINDOW_HXX__
#define MAINWINDOW_HXX__

#include "Types.hxx"

#include "WinAPI.hxx"
#include "WindowMover.hxx"
#include "HotKeys.hxx"

#include <vector>

namespace clime {

    class Config;
    class TextBox;
    class ListBox;
    class Candidates;
    class EngineProxy;

    class MainWindow : private WindowMover {
    private:
        enum class DrawMode {
            OPAQ    = 0,
            KEEP    = 1,
            TRAN    = 2
        };
    private:
        using KeyHandler = void (MainWindow::*)( HWND, int, DrawMode& );
    public:
        MainWindow() = delete;
        MainWindow( HINSTANCE hInstance,
                    const wchar_t* pModulePath, const Config& cfg );
        MainWindow( const MainWindow& ) = delete;
        ~MainWindow();
        MainWindow& operator=( const MainWindow& ) = delete;

    private:
        static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

    public:
        int DoModal( int cmdShow );
        LRESULT OnMessage( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    private:
        void CalcWindowSize( int& width, int& height );
        void Initialize( HWND hwnd );
        void Finish( HWND hwnd );
        void RegisterWord();
        void DeleteWord();
        void ResetConv( HWND hwnd, bool bEnable = true );
        void Search( HWND hwnd, bool bNext = false );
        void SelectCandidate();
        void ProcessKey( HWND hwnd, int keyCode );
        bool InsertText();
        void SetupRegion( HWND hwnd );
        HRGN CreateBelowRegion( const RECT& rect );
        HRGN CreateAboveRegion( const RECT& rect );
        void Display( HWND hwnd, DrawMode mode );

    private:
        void OnEmptyKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnNormalKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlJ( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlA( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlB( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlD( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlE( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlF( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlK( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlG( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlQ( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlO( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlT( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlN( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlP( HWND hwnd, int keyCode, DrawMode& mode );
        void OnAltQ( HWND hwnd, int keyCode, DrawMode& mode );
        void OnAltJ( HWND hwnd, int keyCode, DrawMode& mode );
        void OnAltW( HWND hwnd, int keyCode, DrawMode& mode );
        void OnBackSpaceKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnDeleteKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnEscapeKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnSpaceKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnEnterKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCursorKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnHomeKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnEndKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlSemicolon( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlColon( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlSpace( HWND hwnd, int keyCode, DrawMode& mode );
        void OnCtrlNumber( HWND hwnd, int keyCode, DrawMode& mode );
        void OnNumber( HWND hwnd, int keyCode, DrawMode& mode );
        void OnNextTheme( HWND hwnd, int keyCode, DrawMode& mode );
        void OnHelpKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnVersionKey( HWND hwnd, int keyCode, DrawMode& mode );
        void OnRecallResult( HWND hwnd, int keyCode, DrawMode& mode );
        void OnToggleIndexing( HWND hwnd, int keyCode, DrawMode& mode );
        void OnToggleDirectKey( HWND hwnd, int keyCode, DrawMode& mode );

    private:
        const wchar_t* GetTargetImageName( HWND hWnd );
        uint32_t SelectSendMethod( const wchar_t** ppExeName );
        void SimulateKeyEvent( int key, int bucky1, int bucky2 );
        void SimulateKeyEvent( HWND hwnd, int hotKey, int key, int bucky = 0 );
        void RegisterHotKeys();
        bool DoInputBox( const wchar_t* pTitle,
                         const wchar_t* pPrompt, wchar_t* pBuf, uint32_t bufLen );

    private:
        virtual void OnChangePosition( HWND hwnd, WindowMover::Position pos );

    private:
        const HINSTANCE m_hThisInstance;
        std::wstring    m_helpPath;
        const Config&   m_config;
        int             m_wndWidth;
        int             m_wndHeight;
        HWND            m_hWnd;
        HRGN            m_rgnBelow;
        HRGN            m_rgnAbove;
        DWORD           m_lastDrawTime;
        DrawMode        m_lastDrawMode;
        EngineProxy*    m_pEngine;
        TextBox*        m_pTxtBox;
        ListBox*        m_pLstBox;
        Candidates*     m_pCands;
        std::wstring    m_lastResult;
        bool            m_bIndexing;
        bool            m_bDirectKeying;
        bool            m_bConverting;
        std::wstring    m_inputs;
        bool            m_exactMatch;
        HFONT           m_hFont;
        KeyHandler      m_keyHandlers[256];
        HotKeys         m_baseHotKeys;
        HotKeys         m_ctrlHotKeys;
        HotKeys         m_emacsHotKeys;
        HotKeys         m_charHotKeys;
    };

} // namespace clime

#endif // MAINWINDOW_HXX__
