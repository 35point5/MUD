//
// Created by Mogician on 2022/5/3.
//

#ifndef PROJECT_SUPPLIER_H
#define PROJECT_SUPPLIER_H

#include "entity/Item.h"
#include "entity/Gun.h"
namespace MUD {
    const int RecipeCnt=3;
    const int Recipe[RecipeCnt][MaxItemCnt]={{0,0,2,1},{0,0,30},{0,0,1,0,1}};
    const std::vector<Item*> Product[RecipeCnt]={{new Item(Sword,1)},{new Gun(1)},{new Item(Bullet,1)}};
    class Supplier {
    private:
        std::vector<Item*> storage;
        bool disabled;
    public:
        Supplier();
        void Deposit(Item *item);
        Item *Withdraw(int index);
        inline bool IsDisabled(){return disabled;}
        std::string ShowInfo();
    };

} // MUD

#endif //PROJECT_SUPPLIER_H
