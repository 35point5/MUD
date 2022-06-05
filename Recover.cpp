//
// Created by Mogician on 2022/6/5.
//

#include "Recover.h"

namespace MUD {
    Timer Recover::timer;

    Recover::Recover(int rate,int val,int maxVal) : rate(rate), val(val),maxVal(maxVal), lastTime(timer.TimeMS()) {

    }

    void Recover::update() {
        long long curTime = timer.TimeMS();
        long long inc = (curTime - lastTime) / rate;
        lastTime += inc * rate;
        val += inc;
        if (val>maxVal) val=maxVal;
    }
} // MUD