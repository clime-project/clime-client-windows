//------------------------------------------------------------------------------
//
// ListBox.hxx
//
//------------------------------------------------------------------------------
#ifndef LISTBOX_HXX__
#define LISTBOX_HXX__

#include "Box.hxx"

#include <stdint.h>

namespace clime {

    class Config;
    class Candidates;

    class ListBox : public Box {
    public:
        ListBox() = delete;
        ListBox( const Config& cfg );
        ListBox( const ListBox& ) = delete;
        virtual ~ListBox();
        ListBox& operator=( const ListBox& ) = delete;
    public:
        void DrawListBox( HDC hdc, const Config& cfg, bool bIndexing,
                          int xOffset, const Candidates& cands, const RECT& rect );
    protected:
        virtual void AfterFill( const ColorTheme& theme,
                                HDC hdc, const RECT& rect, void* pOpaque );
    private:
        uint32_t m_indexWidth;
    };

} // namespace clime

#endif // LISTBOX_HXX__
