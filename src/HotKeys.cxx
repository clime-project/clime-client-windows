//------------------------------------------------------------------------------
//
// HotKeys.cxx
//
//------------------------------------------------------------------------------
#include "HotKeys.hxx"

namespace clime {

    HotKeys::HotKeys() : m_bEnabled( false ),
                         m_entries() {
    }

    HotKeys::~HotKeys() {
    }

    void HotKeys::AddKey( int hotKey, UINT bucky, UINT vkey ) {
        //ToDo : check duplication...?
        m_entries.emplace_back( hotKey, bucky, vkey );
    }

    void HotKeys::Enable( HWND hwnd ) {
        if( !m_bEnabled ) {
            for( const auto& entry : m_entries )
                WinAPI::RegisterHotKey( hwnd,
                                        std::get<0>( entry ),
                                        std::get<1>( entry ),
                                        std::get<2>( entry ) );
            m_bEnabled = true;
        }
    }

    void HotKeys::Disable( HWND hwnd ) {
        if( m_bEnabled ) {
            for( const auto& entry : m_entries )
                WinAPI::UnregisterHotKey( hwnd, std::get<0>( entry ) );
            m_bEnabled = false;
        }
    }

} // namespace clime

