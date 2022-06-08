//
// Created by Mogician on 2022/5/3.
//

#ifndef PROJECT_SUPPLIER_H
#define PROJECT_SUPPLIER_H

#include "Item.h"

namespace MUD {
    const int RecipeCnt=3;
    const int Recipe[RecipeCnt][MaxItemCnt]={{0,0,2,1},{0,0,30},{0,0,1,0,1}};
    const int Product[RecipeCnt][MaxItemCnt]={{0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,0,1}};
    class Supplier {
    private:
        std::vector<Item*> storage;
    public:
        Supplier();
        void Deposit(Item *item);
        Item *Withdraw(int itype);
    };

} // MUD

#endif //PROJECT_SUPPLIER_H
