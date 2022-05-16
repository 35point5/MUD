//
// Created by root on 5/15/22.
//

#ifndef MUD_MUDEXCEPTION_H
#define MUD_MUDEXCEPTION_H

#include "exception"

namespace MUD {
    enum Error {
        // errors that shouldn't happen, so if they do, something is wrong:
        ESeriousError,

        // these errors are common
        ENetworkDown,
        ENoSocketsAvailable,
        ENoMemory,
        EAddressNotAvailable,
        EAlreadyConnected,
        ENotConnected,
        EConnectionRefused,
        ENetworkUnreachable,
        ENetworkReset,
        EHostUnreachable,
        EHostDown,
        EConnectionAborted,
        EConnectionReset,
        EOperationWouldBlock,

        // DNS errors
        EDNSNotFound,
        EDNSError,
        ENoDNSData,

        // These errors are specific errors that should never or rarely occur.
        EInProgress,
        EInterrupted,
        EAccessDenied,
        EInvalidParameter,
        EAddressFamilyNotSupported,
        EProtocolFamilyNotSupported,
        EProtocolNotSupported,
        EProtocolNotSupportedBySocket,
        EOperationNotSupported,
        EInvalidSocketType,
        EInvalidSocket,
        EAddressRequired,
        EMessageTooLong,
        EBadProtocolOption,
        EAddressInUse,
        ETimedOut,
        EShutDown,


        // auxilliary socketlib errors
        ESocketLimitReached,
        ENotAvailable,
        EConnectionClosed
    };

    class MUDException : public std::exception {
    protected:
        Error code;
    public:
        MUDException(Error c):code(c){}
        inline Error Reason(){return code;}
    };

} // MUD

#endif //MUD_MUDEXCEPTION_H
