//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include "mysql++/mysql++.h"
#include "mysql++/tcp_connection.h"
#include <string>
#include <iostream>
#include "Entity.h"
#include "../socket/Telnet.h"
#include "string"
#include "Creature.h"

namespace MUD {
    enum Role {
        guest,
        common,
        admin
    };

    class Room;

    class Item;

    class Player : public Creature {
        friend class boost::serialization::access;

    private:
        Room *currentRoom;
        std::vector<Item *> items;
        Connection<Telnet> *conn;
        std::string password;
        Role role;
    public:
        static int DefaultHP;
        static int DefaultAP;
        static int DefaultHeal;

        Player(Connection<Telnet> &);

        ~Player();

        void Enter(Room *r);

        void GetItem(Item *item);

        inline Room *CurrentRoom() { return currentRoom; }

        std::string ShowItems();

        void Sendln(const std::string &s);

        int ItemCnt(int id);

        inline void InvalidCommand() {
            Sendln(red + "Invalid command, use \"help\" to show help.");
        }

        static bool PlayerExist(const std::string &name);

        static bool AuthPlayer(const std::string &name, const std::string &password);

        void Save(const std::string &info);

        static mysqlpp::StoreQueryResult FindPlayer(const std::string &name);

        Player *Create(const std::string &ar, Connection<Telnet> &conn);

        bool Register(const std::string &p_name, const std::string &p_password);

        bool Login(const std::string &p_name, const std::string &p_password);

        std::string SerializeTo();

        void UnserializeFrom(const std::string &s);

        inline Role GetRole() { return role; }

        void Deathrattle(Room *cur_room, Creature *);

        int RemoveItem(int itemType, int number = 0);

        inline void ClearBuf(){conn->ClearBuf();}

        void Use(int index, int num);

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & name;
            ar & password;
            ar & role;
            ar & items;
        }

        Item *FetchItem(int itemType);
    };

}


#endif //PROJECT_PLAYER_H
