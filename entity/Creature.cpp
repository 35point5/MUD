//
// Created by Mogician on 2022/6/4.
//

#include "Creature.h"

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
} // MUD