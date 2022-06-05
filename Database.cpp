//
// Created by Mogician on 2022/6/3.
//

#include "Database.h"
#include "fstream"
#include "glog/logging.h"
namespace MUD {
    mysqlpp::Connection Database::Conn(false);
    mysqlpp::Query Database::InsertPlayer(&Conn);
    mysqlpp::Query Database::FindPlayer(&Conn);
    mysqlpp::Query Database::AuthPlayer(&Conn);
    mysqlpp::Query Database::UpdatePlayer(&Conn);
    bool Database::Connect(const std::string &db, const std::string &server, const std::string &user,
                           const std::string &password, uint32_t port) {
        return Conn.connect(db.data(), server.data(), user.data(), password.data(), port);
    }

    bool Database::Init() {
        std::ifstream f;
        f.open("database.txt");
        std::string db,server,user,password;
        uint32_t port;
        std::getline(f,db);
        std::getline(f,server);
        std::getline(f,user);
        std::getline(f,password);
        f>>port;
        bool res=Connect(db,server,user,password,port);
        InsertPlayer=Conn.query("insert into players (name,password,info) values (%0q,%1q,%2q);");
        InsertPlayer.parse();
        FindPlayer=Conn.query("select * from players where name=%0q;");
        FindPlayer.parse();
        AuthPlayer=Conn.query("select * from players where name=%0q and password=%1q;");
//        AuthPlayer=Conn.query("select * from players;");
        AuthPlayer.parse();
        UpdatePlayer=Conn.query("update players set name=%0q,password=%1q,info=%2q where name=%3q;");
        UpdatePlayer.parse();
        return res;
    }
} // MUD