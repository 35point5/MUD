//
// Created by Mogician on 2022/6/3.
//

#ifndef MUD_DATABASE_H
#define MUD_DATABASE_H
#include "mysql++/mysql++.h"
#include "mysql++/tcp_connection.h"

namespace MUD {

    class Database {
    public:
        static mysqlpp::Connection Conn;
        static mysqlpp::Query InsertPlayer;
        static mysqlpp::Query FindPlayer;
        static mysqlpp::Query AuthPlayer;
        static mysqlpp::Query UpdatePlayer;
        static bool Connect(const std::string &db, const std::string &server, const std::string &user, const std::string &password, uint32_t port);
        static bool Init();
    private:

        

    };

} // MUD

#endif //MUD_DATABASE_H
