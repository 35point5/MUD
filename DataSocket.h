//
// Created by root on 5/11/22.
//

#ifndef MUD_DATASOCKET_H
#define MUD_DATASOCKET_H

#include "Socket.h"
#include "string"
#include "glog/logging.h"
#include "glog/raw_logging.h"
namespace MUD {

    class DataSocket: public Socket{
    protected:
        bool connected;
        sockaddr_in remoteInfo;
    public:
        DataSocket(sockType socket=-1);
        void Connect(IPAddrType addr, portType port);
        int Send(const char *buf, int len);
        int Receive(char *buf,int len);
        void Close() override;
        inline std::string IP(){return inet_ntoa(remoteInfo.sin_addr);}
    };

} // MUD

#endif //MUD_DATASOCKET_H
