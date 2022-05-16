//
// Created by root on 5/13/22.
//

#include "Telnet.h"

namespace MUD {
    void Telnet::Translate(Connection<Telnet> &conn,const char *buf, int len) {
        for (int i=0;i<len;++i){
            char c=buf[i];
            if (c>=0x20 && c<0x7F && bufLen<BUFSIZE){
                buffer[bufLen++]=c;
            }
            else if (c==8 && bufLen){
                --bufLen;
            }
            else if (c=='\n' || c=='\r'){
                if (bufLen && conn.Handler()!= nullptr){
                    conn.Handler()->Handle(std::string(buffer,bufLen));
                }
                bufLen=0;
            }
        }
    }

    void Telnet::SendString(Connection<Telnet> &conn, const std::string &s) {
        conn.AppendBuf(s.data(),s.length());
    }
} // MUD