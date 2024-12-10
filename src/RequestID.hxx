//------------------------------------------------------------------------------
//
// RequestID.hxx
//
//------------------------------------------------------------------------------
#ifndef REQUESTID_HXX__
#define REQUESTID_HXX__

namespace clime {

    enum class RequestID : char {
        DISCONNECT      = '0',
        EXECSEARCH      = '1',
        GETVERSION      = '2',
        GETHOSTNAME     = '3',
        SETCONTEXT      = '4',
        REGWORD         = '5',
        DELWORD         = '6',
        SAVEDICT        = '7',
        NOTIFYSELECTION = '8',
        CLEARCONTEXT    = 'C',
        GETDEFINITION   = 'D',
        ENUMDICTIONARY  = 'E',
        DICTIONARYINFO  = 'I',
        SETLOGLEVEL     = 'L',
        EXECSEARCHNEXT  = 'N',
        SETCANDLIMIT    = 'R',
        EXECSEARCH2S    = 'S',
        REGWORD2        = 'T',
        DELWORD2        = 'U',
        SHUTDOWN        = 'Q',
        WRITELOG        = 'W',
        EXECSEARCH2X    = 'X'
    };

    class ReadBuffer;
    class WriteBuffer;
    const ReadBuffer& operator>>( const ReadBuffer& rb, RequestID& req );
    WriteBuffer& operator<<( WriteBuffer& wb, RequestID  req );

} // namespace clime

#endif // REQUESTID_HXX__
