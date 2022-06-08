//
// Created by Mogician on 2022/6/8.
//

#ifndef MUD_DOG_H
#define MUD_DOG_H
#include "Mob.h"
#include "Room.h"
namespace MUD {

    class Dog: public Mob {
    public:
        void Deathrattle(Room *room, Creature *creature) override;
        Dog(int r=0,int h=4,int a=2): Mob(r,h,a){};
    };

} // MUD

#endif //MUD_DOG_H
