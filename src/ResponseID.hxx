//------------------------------------------------------------------------------
//
// ResponseID.hxx
//
//------------------------------------------------------------------------------
#ifndef RESPONSEID_HXX__
#define RESPONSEID_HXX__

namespace clime {

    enum class ResponseID : char {
        ERROR           = '0',
        COMPLETE        = '1',
        NO_CANDIDATE    = '4'
    };

    class ReadBuffer;
    class WriteBuffer;
    const ReadBuffer& operator>>( const ReadBuffer& rb, ResponseID& req );
    WriteBuffer& operator<<( WriteBuffer& wb, ResponseID  req );

} // namespace clime

#endif // RESPONSEID_HXX__
