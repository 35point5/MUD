//
// Created by Mogician on 2022/6/4.
//

#include "Creature.h"

namespace MUD {
    bool Creature::Attack(Creature &enemy) {
        int enemyHP=enemy.hp.Get();
        enemyHP-=ap;
        enemy.hp.SetVal(enemyHP);
        return enemyHP<=0;
    }

    bool Creature::GetHurt(int damage) {
        int oldHP=hp.Get();
        oldHP-=damage;
        hp.SetVal(oldHP);
        return oldHP<0;
    }
} // MUD