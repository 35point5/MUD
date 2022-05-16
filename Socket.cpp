//
// Created by root on 5/11/22.
//

#include "Socket.h"
#include "iostream"
MUD::Socket::Socket(MUD::sockType socket) : sock(socket) {
    if (socket != -1) {
        socklen_t s = sizeof(localInfo);
        getsockname(socket,(sockaddr*)&localInfo,&s);
    }
    blocked=true;
}

void MUD::Socket::Close() {
    close(sock);
    sock=-1;
}

void MUD::Socket::SetBlock(bool isBlock) {
    int err;
    int flags= fcntl(sock,F_GETFL,0);
    if (isBlock) flags&=~O_NONBLOCK; else flags|=O_NONBLOCK;
    err= fcntl(sock,F_SETFL,flags);
    blocked=isBlock;
    std::cout<<"setblock:"<<err<<std::endl;
}
