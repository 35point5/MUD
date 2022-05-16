//
// Created by root on 5/13/22.
//

#ifndef MUD_TELNET_H
#define MUD_TELNET_H
#include "Connection.h"
#include "ConnectionHandler.h"
namespace MUD {
    const std::string reset = "\x1B[0m";
    const std::string bold = "\x1B[1m";
    const std::string dim = "\x1B[2m";
    const std::string under = "\x1B[4m";
    const std::string reverse = "\x1B[7m";
    const std::string hide = "\x1B[8m";

    const std::string clearscreen = "\x1B[2J";
    const std::string clearline = "\x1B[2K";

    const std::string black = "\x1B[30m";
    const std::string red = "\x1B[31m";
    const std::string green = "\x1B[32m";
    const std::string yellow = "\x1B[33m";
    const std::string blue = "\x1B[34m";
    const std::string magenta = "\x1B[35m";
    const std::string cyan = "\x1B[36m";
    const std::string white = "\x1B[37m";

    const std::string bblack = "\x1B[40m";
    const std::string bred = "\x1B[41m";
    const std::string bgreen = "\x1B[42m";
    const std::string byellow = "\x1B[43m";
    const std::string bblue = "\x1B[44m";
    const std::string bmagenta = "\x1B[45m";
    const std::string bcyan = "\x1B[46m";
    const std::string bwhite = "\x1B[47m";

//    const std::string newline = "\r\n\x1B[0m";
    const std::string newline = "\r\n"+white;
    class Telnet {
    protected:
        char buffer[BUFSIZE];
        int bufLen;
    public:
        typedef ConnectionHandler<Telnet,std::string> handler;
        void Translate(Connection<Telnet> &conn,const char *buf,int len);
        void SendString(Connection<Telnet> &conn, const std::string& s);
    };

} // MUD

#endif //MUD_TELNET_H
