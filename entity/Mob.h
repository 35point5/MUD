//
// Created by Mogician on 2022/6/4.
//

#ifndef MUD_MOB_H
#define MUD_MOB_H
#include "Creature.h"

namespace MUD {
    class Dog;
    class Mob: public Creature{
    public:
        static std::vector<Mob*> Instance;
        Mob(int r,int h,int a): Creature(r,h,a){};
        virtual Mob* CopyMob(){return new Mob(*this);};
    };

} // MUD

#endif //MUD_MOB_H
