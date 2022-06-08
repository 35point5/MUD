//
// Created by Mogician on 2022/5/1.
//

#include "Item.h"

namespace MUD {
    std::string Item::ItemInfo[MaxItemCnt]={"water","food","metal","wood","gunpowder","key of farm","key of BlastFurnance","caller to the sun","the Reconstructor","sword","gun","bullet"};

    Item::Item(int t, int num) : itemType(t), number(num){}
} // MUD