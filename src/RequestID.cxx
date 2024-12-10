//------------------------------------------------------------------------------
//
// RequestID.cxx
//
//------------------------------------------------------------------------------
#include "RequestID.hxx"

#include "ReadBuffer.hxx"
#include "WriteBuffer.hxx"

namespace clime {

    const ReadBuffer& operator>>( const ReadBuffer& rb, RequestID& req ) {
        char c;
        rb >> c;
        req = (RequestID)c;
        return rb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, RequestID req ) {
        wb << (char)req;
        return wb;
    }

} // namespace clime

