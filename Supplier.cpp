//
// Created by Mogician on 2022/5/3.
//

#include "Supplier.h"

namespace MUD {
    void Supplier::Deposit(Item *item) {
        storage.push_back(item);
    }

    Item *Supplier::Withdraw(int itype) {
        for (auto it = storage.begin(); it != storage.end(); ++it)
            if ((*it)->ItemType() == itype) {
                auto res = *it;
                storage.erase(it);
                return res;
            }
        return nullptr;
    }

    Supplier::Supplier():disabled(true){};
} // MUD