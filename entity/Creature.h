//
// Created by Mogician on 2022/6/4.
//

#ifndef MUD_CREATURE_H
#define MUD_CREATURE_H
#include "Entity.h"
#include "functional"
#include "../Recover.h"
#include "../socket/Telnet.h"
#include "Item.h"

namespace MUD {
//    class Player;
    class Room;
    class Creature: public Entity{
    protected:
        int ap;
        Recover hp;
    public:
        Creature(int r,int h,int a):hp(r,h,h),ap(a){};
        virtual bool Attack(Creature &enemy);
        virtual void Deathrattle(Room *,Creature *){};
        virtual void Sendln(const std::string &s){};
        inline int GetHP() {return hp.Get();}
        inline int GetAP() {return ap;}
        bool GetHurt(int damage);
        inline int Heal(int healHP){hp.SetVal(hp.Get()+healHP);  return hp.Get();}
        inline int MaxHP(){return hp.MaxVal();}
        static void Drop(Room *room, Creature *creature, std::vector<std::pair<Item *, int>> &drop);
        inline std::string CreatureInfo(){
            std::stringstream ss;
            ss << "A " << GetName() << " HP:" << GetHP() << " DMG:" << GetAP();
            return ss.str();
        }
    };

} // MUD

#endif //MUD_CREATURE_H
