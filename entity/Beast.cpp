//
// Created by Mogician on 2022/6/10.
//

#include "Beast.h"
#include "Item.h"
namespace MUD {
    std::vector<std::pair<Item *, int>> Beast::drop={std::make_pair(new Item(Gunpowder,3),50),std::make_pair(new Item(Metal,3),100)};
    void Beast::Deathrattle(Room *room, Creature *creature) {
        Creature::Drop(room, creature,Beast::drop);
    }

    Mob *Beast::CopyMob() {
        return new Beast(*this);
    }
} // MUD