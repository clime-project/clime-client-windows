//------------------------------------------------------------------------------
//
// SendMethod.cxx
//
//------------------------------------------------------------------------------
#include "SendMethod.hxx"

namespace clime {

    enum SendMethodType {
        SENDMETHOD_PASTE  = 1,
        SENDMETHOD_WINMSG = 2
    };

    union SendMethodData {
        struct {
            int32_t   type: 4;
            int32_t  dummy: 4;
            int32_t bucky1: 8;
            int32_t bucky2: 8;
            int32_t    key: 8;
        } paste;
        struct {
            int32_t      type: 4;
            uint32_t interval: 8;
            int32_t      code:20;
        } message;
        uint32_t value;
    };


    bool SendMethod::IsWinMessage( uint32_t value ) {
        return (reinterpret_cast<SendMethodData*>( &value )->message.type == SENDMETHOD_WINMSG);
    }
    uint32_t SendMethod::MakeWinMesasge( uint32_t msgCode, uint32_t msecInterval ) {
        SendMethodData d;
        d.message.type     = SENDMETHOD_WINMSG;
        d.message.interval = (msecInterval < 0x000000FFu) ? msecInterval : 0x000000FFu;
        d.message.code = msgCode;
        return d.value;
    }
    uint32_t SendMethod::MakePasteKey( int32_t bucky1, int32_t bucky2, int32_t key ) {
        SendMethodData d;
        d.paste.type   = SENDMETHOD_PASTE;
        d.paste.dummy  = 0;
        d.paste.bucky1 = bucky1;
        d.paste.bucky2 = bucky2;
        d.paste.key    = key;
        return d.value;
    }
    uint32_t SendMethod::GetWinMessage( uint32_t value, uint32_t& msecInterval ) {
        auto p = reinterpret_cast<SendMethodData*>( &value );
        if( p->message.type != SENDMETHOD_WINMSG )
            return 0;
        msecInterval = p->message.interval;
        return p->message.code;
    }
    bool SendMethod::GetPastekey( uint32_t value,
                                  int32_t& bucky1, int32_t& bucky2, int32_t& key ) {
        auto p = reinterpret_cast<SendMethodData*>( &value );
        if( p->paste.type != SENDMETHOD_PASTE )
            return false;
        bucky1   = p->paste.bucky1;
        bucky2   = p->paste.bucky2;
        key      = p->paste.key;
        return true;
    }

} // namespace clime

