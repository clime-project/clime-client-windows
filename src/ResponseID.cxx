//------------------------------------------------------------------------------
//
// ResponseID.cxx
//
//------------------------------------------------------------------------------
#include "ResponseID.hxx"

#include "ReadBuffer.hxx"
#include "WriteBuffer.hxx"

namespace clime {

    const ReadBuffer& operator>>( const ReadBuffer& rb, ResponseID& res ) {
        char c;
        rb >> c;
        res = (ResponseID)c;
        return rb;
    }

    WriteBuffer& operator<<( WriteBuffer& wb, ResponseID  res ) {
        wb << (char)res;
        return wb;
    }

} // namespace clime

