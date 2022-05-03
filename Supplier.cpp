//
// Created by Mogician on 2022/5/3.
//

#include "Supplier.h"

namespace MUD {
    int Supplier::Deposit(int itype, int num) {
        Storage[itype]->Number()+=num;
        return num;
    }

    int Supplier::Withdraw(int itype, int num) {
        num=std::min(num,Storage[itype]->Number());
        Storage[itype]->Number()-=num;
        return num;
    }

    Supplier::Supplier(){
        for (int i = 0; i < MaxItemCnt; ++i) {
            Storage[i]=new Item(i);
        }
    }
} // MUD