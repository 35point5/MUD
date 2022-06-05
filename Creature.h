//
// Created by Mogician on 2022/6/4.
//

#ifndef MUD_CREATURE_H
#define MUD_CREATURE_H
#include "Entity.h"
#include "functional"
#include "Recover.h"
namespace MUD {
//    class Player;
    class Room;
    class Creature: public Entity{
    protected:
        int ap;
        Recover hp;
    public:
        Creature(int r,int h,int a):hp(r,0,h),ap(a){};
        virtual bool Attack(Creature &enemy);
        virtual void Deathrattle(Room *,Creature *){};
        virtual void Sendln(const std::string &s){};
        inline int GetHP() {return hp.Get();}
        inline int GetAP() {return ap;}
        bool GetHurt(int damage);
    };

} // MUD

#endif //MUD_CREATURE_H
