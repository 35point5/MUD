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

    Generator::Generator(int t, int r, int c, int f) : remain((f ? f : DefaultFrequency[t]) * 1000, r,
                                                              c ? c : DefaultCapacity[t]), itemType(t),
                                                       disabled(false) {

    }


    int Generator::Harvest() {
        int r = remain.Get();
        remain.SetVal(0);
        return r;
    }
} // MUD