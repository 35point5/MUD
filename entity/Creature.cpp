//
// Created by Mogician on 2022/6/4.
//

#include "Creature.h"
#include "random"
#include "../Room.h"
extern std::mt19937 mt;
namespace MUD {
    bool Creature::Attack(Creature &enemy) {
        bool killed=enemy.GetHurt(ap);
        Sendln(cyan + "You attack " + enemy.GetName() + ", cause " + std::to_string(ap) + " damage.");
        enemy.Sendln(red+name+" attack you, causing "+std::to_string(ap)+" damage.");
        if (killed){
            Sendln(green + "You defeat " + enemy.GetName() + "!");
            enemy.Sendln(red+"You are defeated by "+name+"!");
        }
        return killed;
    }

    bool Creature::GetHurt(int damage) {
        int oldHP=hp.Get();
        oldHP-=damage;
        hp.SetVal(oldHP);
        return oldHP<0;
    }

    void Creature::Drop(Room *room, Creature *creature, std::vector<std::pair<Item *, int>> &drop) {
        std::uniform_int_distribution<int> rnd(1,100);
        for (auto o:drop){
            int rp=rnd(mt);
            auto it=o.first->CopyItem();
            if (rp<=o.second){
                room->AddItem(it);
                creature->Sendln("Drop "+it->GetInfo()+" .");
            }
        }
    }
} // MUD