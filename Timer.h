//
// Created by Mogician on 2022/4/30.
//
#include "ctime"
#include "chrono"

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

namespace MUD {

    class Timer {
    public:
        int TimeTicks();
        int TimeS();
    };
    inline int Second(int t) {return t*CLOCKS_PER_SEC;}
} // MUD

#endif //PROJECT_TIMER_H
