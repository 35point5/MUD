//
// Created by Mogician on 2022/4/30.
//
#include "sys/time.h"
#include "unistd.h"

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

namespace MUD {

    class Timer {
    public:
        long long int TimeMS();
        long long int TimeS();
    };
} // MUD

#endif //PROJECT_TIMER_H
