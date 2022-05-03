//
// Created by Mogician on 2022/4/30.
//

#include "Timer.h"

namespace MUD {
    int MUD::Timer::TimeTicks() {
        return clock();
    }

    int Timer::TimeS() {
        return clock()/CLOCKS_PER_SEC;
    }
} // MUD