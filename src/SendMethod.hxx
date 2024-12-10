//------------------------------------------------------------------------------
//
// SendMethod.hxx
//
//------------------------------------------------------------------------------
#ifndef SENDMETHOD_HXX__
#define SENDMETHOD_HXX__

#include <stdint.h>


namespace clime {

    class SendMethod {
    public:
        static bool IsWinMessage( uint32_t value );
        static uint32_t MakeWinMesasge( uint32_t msgCode, uint32_t msecInterval );
        static uint32_t MakePasteKey( int32_t bucky1, int32_t bucky2, int32_t key );
        static uint32_t GetWinMessage( uint32_t value, uint32_t& msecInterval );
        static bool GetPastekey( uint32_t value,
                                 int32_t& bucky1, int32_t& bucky2, int32_t& key );
    };

} // namespace clime

#endif // SENDMETHOD_HXX__
