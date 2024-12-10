//------------------------------------------------------------------------------
//
// EngineInfo.hxx
//
//------------------------------------------------------------------------------
#ifndef ENGINEINFO_HXX__
#define ENGINEINFO_HXX__

#include "Common.hxx"

#include <stdint.h>
#include <string>

namespace clime {

    class EngineInfo {
    public:
        EngineInfo() = delete;
        EngineInfo( std::string srvName,
                    uint32_t srvPort, uint32_t candMax ) : m_srvName( srvName ),
                                                           m_srvPort( srvPort ),
                                                           m_candMax( candMax ) {
        }
        EngineInfo( const EngineInfo& ) = delete;
        ~EngineInfo() {}
        EngineInfo& operator=( const EngineInfo& ) = delete;
    public:
        inline std::string ServerName() const { return m_srvName; }
        inline uint32_t PortNumber() const { return m_srvPort; }
        inline uint32_t CandidateMax() const { return m_candMax; }
    private:
        std::string m_srvName;
        uint32_t    m_srvPort;
        uint32_t    m_candMax;
    };

} // namespace clime

#endif // ENGINEINFO_HXX__
