//------------------------------------------------------------------------------
//
// SocketClient.hxx
//
//------------------------------------------------------------------------------
#ifndef SOCKETCLIENT_HXX__
#define SOCKETCLIENT_HXX__

#include <stdint.h>

namespace clime {

    class ReadBuffer;
    class WriteBuffer;

    class SocketClient {
    public:
        SocketClient() = delete;
        SocketClient( const char* pSrvName, uint32_t portNumber );
        SocketClient( const SocketClient& ) = delete;
        ~SocketClient();
        SocketClient& operator=( const SocketClient& ) = delete;
    public:
        inline int GetSocket() { return m_socket; }
        inline ReadBuffer& GetReadBuf() { return *m_pReadBuf; }
        inline WriteBuffer& GetWriteBuf() { return *m_pWriteBuf; }
    private:
        int           m_socket;
        ReadBuffer*   m_pReadBuf;
        WriteBuffer*  m_pWriteBuf;
    };

}  // namespace clime

#endif // SOCKETCLIENT_HXX__
