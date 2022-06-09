//
// Created by Mogician on 2022/5/1.
//

#include "Item.h"
#include "Player.h"
#include "../Room.h"
namespace MUD {
    std::string Item::ItemInfo[MaxItemCnt]={"water","food","metal","wood","gunpowder","key","key of BlastFurnance","caller to the sun","the Reconstructor","sword","gun","bullet"};

    Item::Item(int t, int num) : itemType(t), number(num){}

    bool Item::Use(Player *p, Room *) {
        p->Sendln("No effect.");
        return false;
    }
} // MUD