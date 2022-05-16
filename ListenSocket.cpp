//
// Created by root on 5/11/22.
//
#include "iostream"
#include "ListenSocket.h"
#include "DataSocket.h"

namespace MUD {
    void ListenSocket::Listen(portType p) {
        int err=0;
        if (sock==-1){
            sock= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            std::cout<<"lst create socket:"<<sock<<std::endl;
        }
        int reuse=1;
        err=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(reuse));
        std::cout<<"lst setopt:"<<err<<std::endl;
        localInfo.sin_family=AF_INET;
        localInfo.sin_port= htons(p);
        localInfo.sin_addr.s_addr= htonl(INADDR_ANY);

        err=bind(sock,(sockaddr*)&localInfo,sizeof(sockaddr));
        std::cout<<"lst bind:"<<err<<std::endl;

        err= listen(sock,8);
        std::cout<<"listen:"<<err<<std::endl;
    }

    DataSocket ListenSocket::Accept() {
        sockType s;
        sockaddr_in sa;

        socklen_t sz=sizeof(sockaddr);
        s= accept(sock,(sockaddr*)&sa,&sz);
        std::cout<<"accept s:"<<s<<std::endl;

        return DataSocket(s);
    }

    void ListenSocket::Close() {
        Socket::Close();
        listening=false;
    }
} // MUD