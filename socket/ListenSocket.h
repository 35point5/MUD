//
// Created by root on 5/11/22.
//

#ifndef MUD_LISTENSOCKET_H
#define MUD_LISTENSOCKET_H

#include "Socket.h"
#include "DataSocket.h"

namespace MUD {
    class ListenSocket: public Socket{
    protected:
        bool listening;
    public:
        void Listen(portType p);
        DataSocket Accept();
        void Close() override;
    };

} // MUD

#endif //MUD_LISTENSOCKET_H
