//
// Created by Mogician on 2022/6/8.
//

#include "Dog.h"
#include "Key.h"
namespace MUD {
    std::vector<std::pair<Item *, int>> Dog::drop={std::make_pair(new Item(Wood,3),100), std::make_pair(new Key(FoodType, 1), 10), std::make_pair(new Key(Water, 1), 10), std::make_pair(new Key(Metal, 1), 10)};
    void Dog::Deathrattle(Room *room, Creature *creature) {
        Creature::Drop(room,creature,Dog::drop);
    }

    Mob *Dog::CopyMob() {
        return new Dog(*this);
    }
} // MUD