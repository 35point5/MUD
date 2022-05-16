//
// Created by Mogician on 2022/4/30.
//

#include "Timer.h"

namespace MUD {
    long long int MUD::Timer::TimeMS() {
        timeval t;
        gettimeofday(&t,nullptr);
        return t.tv_sec*1000ll+t.tv_usec/1000;
    }

    long long int Timer::TimeS() {
        timeval t;
        gettimeofday(&t,nullptr);
        return t.tv_sec;
    }
} // MUD