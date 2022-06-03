//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include "mysql++/mysql++.h"
#include "mysql++/tcp_connection.h"
#include <string>
#include <iostream>
#include "Entity.h"
#include "Item.h"
#include "Telnet.h"
#include "string"

namespace MUD{
    enum Role{
        guest,
        common,
        admin
    };
    class Room;
    class Player : public Entity {
        friend class boost::serialization::access;
    private:
        Room *currentRoom;
        Item items[MaxItemCnt];
        Connection<Telnet> *conn;
        std::string password;
        Role role;
    public:
        Player(Connection<Telnet> &);
        ~Player();
        void Enter(Room *r);
        int GetItem(int itemType, int number);
        inline Room *CurrentRoom(){return currentRoom;}
        std::string ShowItems();
        void Sendln(std::string s);
        inline int ItemCnt(int id){return items[id].Number();}
        inline void InvalidCommand(){ Sendln(red+"Invalid command!");}
        static bool PlayerExist(const std::string &name);
        static bool AuthPlayer(const std::string &name,const std::string &password);
        void Save(const std::string &info);
        static mysqlpp::StoreQueryResult FindPlayer(const std::string &name);
        Player *Create(const std::string &ar, Connection <Telnet> &conn);
        bool Register(const std::string &p_name, const std::string &p_password);
        bool Login(const std::string &p_name, const std::string &p_password);
        std::string SerializeTo();
        void UnserializeFrom(const std::string &s);
        inline Role GetRole(){return role;}
        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & name;
            ar & password;
            ar & role;
            int cnt=MaxItemCnt;
            ar & cnt;
            for(int i=0;i<cnt;++i) ar & items[i];
        }
    };

}


#endif //PROJECT_PLAYER_H
