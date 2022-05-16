//
// Created by root on 5/13/22.
//

#ifndef MUD_CONNECTION_H
#define MUD_CONNECTION_H

#include "Socket.h"
#include "DataSocket.h"

namespace MUD {
    const int BUFSIZE = 1024;

    template<class protocol>
    class Connection : public DataSocket {
    protected:
        typename protocol::handler *hand;
        std::string sendBuf;
        protocol prot;
        char buffer[BUFSIZE];
        bool closed;
    public:
        Connection() {};

        Connection(const DataSocket &sock);

        ~Connection();

        void AppendBuf(const char *buf, int len);

        int SendBuf();

        int ReceiveData();

        inline void Close() override { closed = true; }

        inline void CloseSocket() { DataSocket::Close(); }

        void SwitchHandler(typename protocol::handler *h);

        inline typename protocol::handler *Handler() { return hand; }

        inline bool Closed() { return closed; }

        inline void SendString(std::string s) { AppendBuf(s.data(), s.length()); }
    };

    template<class protocol>
    Connection<protocol>::Connection(const DataSocket &sock):DataSocket(sock), hand(nullptr) {}

    template<class protocol>
    void Connection<protocol>::AppendBuf(const char *buf, int len) {
        sendBuf.append(buf, len);
    }

    template<class protocol>
    int Connection<protocol>::SendBuf() {
        if (!sendBuf.length()) return 0;
        int sendLen = Send(sendBuf.data(), sendBuf.length());
        sendBuf.erase(0, sendLen);
        return sendLen;
    }

    template<class protocol>
    int Connection<protocol>::ReceiveData() {
        int len = Receive(buffer, BUFSIZE);
        prot.Translate(*this, buffer, len);
        return len;
    }

    template<class protocol>
    void Connection<protocol>::SwitchHandler(typename protocol::handler *h) {
        if (hand != nullptr) {
            hand->Leave();
            delete hand;
        }
        hand = h;
        h->Enter();
    }

    template<class protocol>
    Connection<protocol>::~Connection() {
        delete hand;
    }
} // MUD



#endif //MUD_CONNECTION_H
