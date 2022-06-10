//
// Created by Mogician on 2022/5/3.
//

#include "Supplier.h"
#include "socket/Telnet.h"

namespace MUD {
    void Supplier::Deposit(Item *item) {
        if (item->IsStackable()){
            for(auto &o:storage) if (o->ItemType()==item->ItemType() && o->IsStackable()){
                    o->Number()+=item->Number();
                    return;
                }
        }
        storage.push_back(item);
    }

    Item *Supplier::Withdraw(int index) {
        if (index>=storage.size()) return nullptr;
        return storage[index];
    }

    Supplier::Supplier():disabled(true){}

    std::string Supplier::ShowInfo() {
        std::stringstream ss;
        if (storage.empty()){
            ss<<cyan+dim+"There is nothing in the supplier."<<newline;
            return ss.str();
        }
        int index=0;
        for (auto o:storage) {
            if (o->Number()) ss<<green<<o->Number()<<"*"<<o->Info()<<", item Index:"<<index<<newline;
            ++index;
        }
        return ss.str();
    };
} // MUD