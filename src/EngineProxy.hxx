//------------------------------------------------------------------------------
//
// EngineProxy.hxx
//
//------------------------------------------------------------------------------
#ifndef ENGINEPROXY_HXX__
#define ENGINEPROXY_HXX__

#include <stdint.h>
#include <functional>

namespace clime {

    struct DictionaryInfo;
    struct SocketClient;
    struct EngineInfo;

    class EngineProxy {
    public:
        using StringReceiver = std::function<bool(const wchar_t*, const wchar_t*)>;
    public:
        EngineProxy() = delete;
        EngineProxy( const EngineInfo& info );
        EngineProxy( const EngineProxy& ) = delete;
        ~EngineProxy();
        EngineProxy& operator=( const EngineProxy& ) = delete;
    public:
        bool Disconnect();
        bool ExecSearch( const wchar_t* pPattern,
                         bool bExact, const StringReceiver& rcv );
        bool ExecSearchNext( const StringReceiver& rcv );
        bool GetVersion( const StringReceiver& rcv );
//      bool GetHostName( const StringReceiver& rcv );
        bool ClearContext();
        bool SetContext( const wchar_t* pContext );
        bool RegWord( const wchar_t* pPattern, const wchar_t* pWord );
        bool DelWord( const wchar_t* pWord );
        bool SaveDict();
        bool NotifySelection( int index );
        bool SetCandidateLimit( uint32_t limit );
//      bool EnumDictionary( const StringReceiver& rcv );
//      bool DictInfo( int index, DictionaryInfo& info, uint32_t& entryCount );
//      bool Shutdown();
    private:
        SocketClient*  m_pSockClient;
    };

}  // namespace clime

#endif // ENGINEPROXY_HXX__
