//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H

#include <string>

namespace MUD {
    const int Water = 0;
    const int Food = 1;
    const int Metal = 2;
    const int MaxItemCnt = 10;

    class Item {
    private:
        int itemType;
        int number;
    public:
        Item(int t);
        static std::string ItemInfo[MaxItemCnt];

        inline int &ItemType() { return itemType; }

        inline int &Number() { return number; }

        inline std::string Info() { return ItemInfo[itemType]; }
    };

} // MUD

#endif //PROJECT_ITEM_H
