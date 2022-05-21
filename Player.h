//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H


#include <string>
#include <iostream>
#include "Entity.h"
#include "Item.h"
#include "Telnet.h"
#include "string"
namespace MUD{
    class Room;
    class Player : public Entity {
    private:
        Room *currentRoom;
        Item *items[MaxItemCnt];
        Connection<Telnet> *conn;
    public:
        Player(Connection<Telnet> &);
        void Enter(Room *r);
        int GetItem(int itemType, int number);
        inline Room *CurrentRoom(){return currentRoom;}
        std::string ShowItems();
        void Sendln(std::string s);
        inline int ItemCnt(int id){return items[id]->Number();}
        inline void InvalidCommand(){ Sendln(red+"Invalid command!");}
    };

}


#endif //PROJECT_PLAYER_H
