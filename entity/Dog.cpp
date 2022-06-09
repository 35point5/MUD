//
// Created by Mogician on 2022/6/8.
//

#include "Dog.h"
#include "Key.h"
#include "random"
extern std::mt19937 mt;
namespace MUD {
    std::vector<std::pair<Item *, int>> Dog::drop={std::make_pair(new Item(Wood,3),100),std::make_pair(new Key(Food,1),10),std::make_pair(new Key(Water,1),10),std::make_pair(new Key(Metal,1),10)};
    void Dog::Deathrattle(Room *room, Creature *creature) {
        std::uniform_int_distribution<int> rnd(1,100);
        for (auto o:drop){
            int rp=rnd(mt);
            auto it=new Item(*o.first);
            if (rp<=o.second) room->AddItem(it);
            creature->Sendln("Drop "+it->GetInfo()+" .");
        }
    }
} // MUD