//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H


#include <string>
#include <iostream>
#include "Entity.h"
#include "Item.h"

namespace MUD{
    class Room;
    class Player : public Entity {
    private:
        Room *currentRoom;
        Item *items[MaxItemCnt];
    public:
        Player();
        void Enter(Room *r);
        int GetItem(int itemType, int number);
        inline Room *CurrentRoom(){return currentRoom;}
        void ShowItems();
    };

}


#endif //PROJECT_PLAYER_H
