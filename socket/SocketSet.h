//
// Created by root on 5/13/22.
//

#ifndef MUD_SOCKETSET_H
#define MUD_SOCKETSET_H
#include "Socket.h"
#include "set"
namespace MUD {

    class SocketSet {
    protected:
        fd_set sockSet;
        fd_set actSet;
        std::set<sockType> set;
    public:
        SocketSet();
        void AddSocket(const Socket& sock);
        void RemoveSocket(const Socket& sock);
        int Poll(int time=0);
        inline bool IsAct(const Socket& sock){
            return FD_ISSET(sock.GetSocket(),&actSet);
        }
    };

} // MUD

#endif //MUD_SOCKETSET_H
