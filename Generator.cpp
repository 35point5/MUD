//
// Created by Mogician on 2022/5/1.
//

#include "Generator.h"
#include "Game.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"

namespace MUD {
    std::string Generator::GeneratorInfo[MaxItemCnt] = {"well", "farm", "mine"};
    int Generator::DefaultCapacity[MaxItemCnt] = {20, 10, 5};
    int Generator::DefaultFrequency[MaxItemCnt] = {10, 30, 60};

    Generator::Generator(Item* t, int r, int c, int f) : remain((f ? f : DefaultFrequency[t->ItemType()]) * 1000, r,
                                                              c ? c : DefaultCapacity[t->ItemType()]), item(t),
                                                       disabled(true) {

    }


    Item * Generator::Harvest() {
        if (disabled) return nullptr;
        int r = remain.Get();
        remain.SetVal(0);
        auto it=item->CopyItem();
        it->Number()*=r;
        return it;
    }
} // MUD