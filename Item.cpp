//
// Created by Mogician on 2022/5/1.
//

#include "Item.h"

namespace MUD {
    std::string Item::ItemInfo[MaxItemCnt]={"水","食物","铁锭"};

    Item::Item(int t):itemType(t),number(0){}
} // MUD