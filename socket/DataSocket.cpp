//
// Created by root on 5/11/22.
//

#include "DataSocket.h"
#include "iostream"

namespace MUD {
    void DataSocket::Connect(IPAddrType addr, portType port) {
        int err;
        if (connected) {
            std::cout << "Already connected." << std::endl;
            return;
        }

        if (sock == -1) {
            sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            std::cout << "data create socket:" << sock << std::endl;
        }

        remoteInfo.sin_family = AF_INET;
        remoteInfo.sin_port = htons(port);
        remoteInfo.sin_addr.s_addr = addr;

        socklen_t s = sizeof(sockaddr);
        err = connect(sock, (sockaddr *) &remoteInfo, s);
        std::cout << "data connect:" << err << std::endl;

        connected = true;

        err = getsockname(sock, (sockaddr *) &localInfo, &s);
        std::cout << "data getsockname:" << err << std::endl;
    }

    int DataSocket::Send(const char *buf, int len) {
        int err;

        if (!connected) {
            std::cout << "No connection!" << std::endl;
            return -1;
        }

        err = send(sock, buf, len, 0);
        std::cout << "data send:" << err << std::endl;
        if (err == EOperationWouldBlock) err = 0;

        return err;
    }

    DataSocket::DataSocket(sockType socket) : Socket(socket) {
        if (socket != -1) {
            socklen_t s = sizeof(remoteInfo);
            getpeername(socket, (sockaddr *) &remoteInfo, &s);
            connected = true;
        } else connected = false;
    }

    void DataSocket::Close() {
        LOG(INFO)<<inet_ntoa(remoteInfo.sin_addr)<<" closed"<<std::endl;
        shutdown(sock, SHUT_RDWR);
        Socket::Close();
        connected = false;
    }

    int DataSocket::Receive(char *buf, int len) {
        int err;
        if (!connected) {
            std::cout << "Receive not connected!" << std::endl;
            return -1;
        }
        err = recv(sock, buf, len, 0);
        for (int i=0;i<err;++i) std::cout<<(int)buf[i]<<' ';
        std::cout<<std::endl;
        std::cout << "data received:" << err << std::endl;
        if (!err) throw MUDException(EConnectionClosed);
        return err;
    }
} // MUD