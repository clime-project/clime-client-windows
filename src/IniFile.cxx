//------------------------------------------------------------------------------
//
// IniFile.cxx
//
//------------------------------------------------------------------------------
#include "IniFile.hxx"

#include "WinAPI.hxx"
#include <string.h>
#include <wchar.h>

namespace clime {

    static constexpr int INITIAL_BUFLEN = 32;

    IniFile::IniFile( const wchar_t* pFileName ) : m_pFileName( nullptr ),
                                                   m_bufLen( INITIAL_BUFLEN ),
                                                   m_pReadBuf( nullptr ) {
        auto len = ::wcslen( pFileName );
        m_pFileName = new wchar_t[len+1];
        ::wcscpy( m_pFileName, pFileName );
        m_pReadBuf = new wchar_t[m_bufLen];
    }

    IniFile::~IniFile() {
        if( !!m_pFileName )
            delete[] m_pFileName;
        if( !!m_pReadBuf )
            delete[] m_pReadBuf;
    }

    const wchar_t* IniFile::Read( const wchar_t* pSection,
                                  const wchar_t* pKey, const wchar_t* pDefault ) const {
        while( true ) {
            int ret = WinAPI::GetPrivateProfileString( pSection, pKey,
                                                       pDefault, m_pReadBuf,
                                                       m_bufLen, m_pFileName );
            if( ret < m_bufLen - 1 )
                break;
            ExpandBuffer();
        }
        return m_pReadBuf;
    }

    bool IniFile::ReadBool( const wchar_t* pSection,
                            const wchar_t* pKey, bool defaultValue ) const {
        auto p = this->Read( pSection, pKey, nullptr );
        if( !p || !*p )
            return defaultValue;
        if( !::wcscmp( p, L"true" ) )
            return true;
        return false;
    }

    void IniFile::ExpandBuffer() const {
        int newLen = m_bufLen * 2;
        wchar_t* pNewBuf = new wchar_t[newLen];
        // MEMO : not copy old buffer contents...
        if( !!m_pReadBuf )
            delete[] m_pReadBuf;
        m_bufLen = newLen;
        m_pReadBuf = pNewBuf;
    }

} // namespace clime

