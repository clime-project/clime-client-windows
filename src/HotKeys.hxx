//------------------------------------------------------------------------------
//
// HotKeys.hxx
//
//------------------------------------------------------------------------------
#ifndef HOTKEYS_HXX__
#define HOTKEYS_HXX__

#include "WinAPI.hxx"

#include <vector>
#include <tuple>

namespace clime {

    class HotKeys {
    private:
        using EntryType = std::tuple<int,UINT,UINT>;
        using ContainerType = std::vector<EntryType>;
    public:
        HotKeys();
        HotKeys( const HotKeys& ) = delete;
        ~HotKeys();
        HotKeys& operator=( const HotKeys& ) = delete;
    public:
        inline bool Enabled() const { return m_bEnabled; }
    public:
        void AddKey( int hotKey, UINT bucky, UINT vkey );
        void Enable( HWND hwnd );
        void Disable( HWND hwnd );
    private:
        bool           m_bEnabled;
        ContainerType  m_entries;
    };

} // namespace clime

#endif // HOTKEYS_HXX__
