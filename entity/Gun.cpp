//
// Created by Mogician on 2022/6/10.
//

#include "Gun.h"
#include "Player.h"
#include "../Room.h"
namespace MUD {
    int Gun::BulletDamage=8;
    int Gun::Use(Player *p, Room *room, int num) {
        if (p->RemoveItem(Bullet,1)){
            p->Sendln(red+"No bullet!");
            return 0;
        }
        auto &mobs=room->GetMobs();
        if (mobs.empty()){
            p->Sendln(red+"No mob here!");
            return 0;
        }
        p->Sendln(green+bold+"Shoot!");
        if (mobs.back()->GetHurt(BulletDamage)){
            mobs.back()->Deathrattle(room,p);
            p->Sendln(green+"You defeat "+mobs.back()->GetName()+"!");
            delete mobs.back();
            mobs.pop_back();
        }
        return 0;
    }

    Item *Gun::CopyItem() {
        return new Gun(*this);
    }
} // MUD
BOOST_CLASS_EXPORT_IMPLEMENT(MUD::Gun);