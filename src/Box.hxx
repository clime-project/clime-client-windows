//------------------------------------------------------------------------------
//
// Box.hxx
//
//------------------------------------------------------------------------------
#ifndef BOX_HXX__
#define BOX_HXX__

#include "WinAPI.hxx"

namespace clime {

    class Config;
    class ColorTheme;

    class Box {
    private:
        using DrawHandler = void (Box::*)( const ColorTheme&,
                                           HDC, const RECT&, void* );
    public:
        Box() = delete;
        Box( const Config& cfg );
        Box( const Box& ) = delete;
        virtual ~Box();
        Box& operator=( const Box& ) = delete;
    public:
        inline void DrawBox( const ColorTheme& theme, HDC hdc,
                             const RECT& rect, void* pOpaque = nullptr ) {
            (this->*m_pHandler)( theme, hdc, rect, pOpaque );
        }
    protected:
        virtual void AfterFill( const ColorTheme&,
                                HDC, const RECT&, void* ) {};
    private:
        void DrawLine( HDC hdc, int x1, int y1, int x2, int y2, HPEN pen );
        void DrawImpForFlat( const ColorTheme&, HDC, const RECT&, void* );
        void DrawImpForSunken( const ColorTheme&, HDC, const RECT&, void* );
        void DrawImpForRaised( const ColorTheme&, HDC, const RECT&, void* );
        void DrawImpForEtched( const ColorTheme&, HDC, const RECT&, void* );
    private:
        DrawHandler m_pHandler;
    };

} // namespace clime

#endif // BOX_HXX__
