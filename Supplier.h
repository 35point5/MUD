//
// Created by Mogician on 2022/5/3.
//

#ifndef PROJECT_SUPPLIER_H
#define PROJECT_SUPPLIER_H

#include "Item.h"

namespace MUD {

    class Supplier {
    private:
        Item *Storage[MaxItemCnt];
    public:
        Supplier();
        int Deposit(int itype, int num);
        int Withdraw(int itype,int num);
    };

} // MUD

#endif //PROJECT_SUPPLIER_H
