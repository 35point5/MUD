//
// Created by Mogician on 2022/6/8.
//

#ifndef MUD_DOG_H
#define MUD_DOG_H

#include "Mob.h"
#include "../Room.h"

namespace MUD {

    class Dog : public Mob {
    private:
        static std::vector<std::pair<Item *, int>> drop;
    public:
        void Deathrattle(Room *room, Creature *creature) override;

        Dog(int r = INT_MAX >> 1, int h = 4, int a = 2) : Mob(r, h, a) { name = "Dog"; description="A kind of weak creature, they are starved, they have no fear.";}

        Mob *CopyMob() override;;
    };



} // MUD

#endif //MUD_DOG_H
