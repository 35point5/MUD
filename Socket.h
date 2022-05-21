//
// Created by root on 5/11/22.
//

#ifndef MUD_SOCKET_H
#define MUD_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include "MUDException.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"
namespace MUD {
    typedef int sockType;
    typedef unsigned long IPAddrType;
    typedef unsigned short portType;
    class Socket {
    protected:
        sockType sock;
        sockaddr_in localInfo;
        bool blocked;
    public:
        Socket(sockType socket=-1);
        inline sockType GetSocket()const {return sock;}
        virtual void Close();
        void SetBlock(bool isBlock);
    };
}


#endif //MUD_SOCKET_H
