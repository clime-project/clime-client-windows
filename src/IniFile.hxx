//------------------------------------------------------------------------------
//
// IniFile.hxx
//
//------------------------------------------------------------------------------
#ifndef INIFILE_HXX__
#define INIFILE_HXX__

namespace clime {

    class IniFile {
    public:
        IniFile( const wchar_t* pFileName );
        ~IniFile();
    public:
        const wchar_t* Read( const wchar_t* pSection,
                             const wchar_t* pKey, const wchar_t* pDefault ) const;
        bool ReadBool( const wchar_t* pSection,
                       const wchar_t* pKey, bool defaultValue ) const;
    public:
        template <typename T>
        inline T ReadString( const wchar_t* pSection,
                             const wchar_t* pKey, const wchar_t* pDefault ) const;
        template <typename T>
        inline T ReadNumeric( const wchar_t* pSection,
                              const wchar_t* pKey, T defaultValue ) const;
    private:
        void ExpandBuffer() const;
    private:
        wchar_t*          m_pFileName;
        mutable int       m_bufLen;
        mutable wchar_t*  m_pReadBuf;
    };


    template <typename T>
    inline T IniFile::ReadString( const wchar_t* pSection,
                                  const wchar_t* pKey, const wchar_t* pDefault ) const {
        return T{ this->Read( pSection, pKey, pDefault ) };
    }

    template <typename T>
    inline T IniFile::ReadNumeric( const wchar_t* pSection,
                                   const wchar_t* pKey, T defaultValue ) const {
        auto p = this->Read( pSection, pKey, nullptr );
        if( !p || !*p )
            return defaultValue;
        T ret = 0;
        for( ; !!*p; ++p )
            ret = (ret * 10) + (*p - '0');
        return ret;
    }

} // namespace clime

#endif // INIFILE_HXX__
