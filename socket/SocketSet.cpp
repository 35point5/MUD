//
// Created by root on 5/13/22.
//

#include "SocketSet.h"

namespace MUD {
    SocketSet::SocketSet() {
        FD_ZERO(&sockSet);
        FD_ZERO(&actSet);
    }

    void SocketSet::AddSocket(const Socket &sock) {
        FD_SET(sock.GetSocket(),&sockSet);
        set.insert(sock.GetSocket());
    }

    void SocketSet::RemoveSocket(const Socket &sock) {
        FD_CLR(sock.GetSocket(),&sockSet);
        set.erase(sock.GetSocket());
    }

    int SocketSet::Poll(int time) {
        timeval t={0,time*1000};
        actSet=sockSet;
        if (!set.size()) return 0;
        return select((*set.rbegin())+1,&actSet,0,0,&t);
    }

} // MUD