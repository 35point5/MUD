//
// Created by Mogician on 2022/6/10.
//

#include "Food.h"
#include "Player.h"
namespace MUD {
    int Food::foodHeal=10;
    int Food::Use(Player *p, Room *room, int num) {
        p->Heal(foodHeal*num);
        p->Sendln(green+"You recover "+ std::to_string(foodHeal*num)+"HP!");
        return num;
    }

    Item *Food::CopyItem() {
        return new Food(*this);
    }
} // MUD
BOOST_CLASS_EXPORT_IMPLEMENT(MUD::Food);