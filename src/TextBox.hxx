//------------------------------------------------------------------------------
//
// TextBox.hxx
//
//------------------------------------------------------------------------------
#ifndef TEXTBOX_HXX__
#define TEXTBOX_HXX__

#include "Types.hxx"

#include "WinAPI.hxx"
#include "Box.hxx"

namespace clime {

    class Config;

    class TextBox : public Box {
    public:
        TextBox() = delete;
        TextBox( const Config& cfg );
        TextBox( const TextBox& ) = delete;
        virtual ~TextBox();
        TextBox& operator=( const TextBox& ) = delete;
    public:
        inline bool Empty() const { return m_text.empty(); }
        inline uint32_t Length() const { return m_text.size(); }
        inline const wchar_t* GetText() const { return m_text.c_str(); }
        inline void SetCaret( uint32_t pos ) { m_caretPos = pos; }
        inline uint32_t GetCaret() const { return m_caretPos; }
        inline wchar_t operator[]( uint32_t idx ) const { return m_text[idx]; }
    public:
        void Clear();
        void Insert( const wchar_t* pUnicodeText );
        void DeleteCaretChar();
        void OperateBackspace();
        void OperateCtrlT();
        void ChompAfterCaret();
    public:
        int DrawTextBox( HDC hdc, const Config& cfg, bool bConverting,
                         const wchar_t* pSelText, int selTextLen, const RECT& rect );
    public:
        uint32_t  GetNextPos() const;
        uint32_t  GetPrevPos() const;
    private:
        std::wstring  m_text;
        uint32_t      m_caretPos;
    };

} // namespace clime

#endif // TEXTBOX_HXX__

