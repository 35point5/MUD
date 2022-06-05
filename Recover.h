//
// Created by Mogician on 2022/6/5.
//

#ifndef MUD_RECOVER_H
#define MUD_RECOVER_H
#include "Timer.h"
#include <climits>
namespace MUD {

    class Recover {
    private:
        static Timer timer;
        int val,maxVal;
        long long lastTime,rate;
        void update();
    public:
        explicit Recover(int rate,int val=0,int maxVal=INT_MAX>>1);
        inline int Get(){update(); return val;}
        inline void SetVal(int v){update(); val=v;}
        inline void SetRate(int r){update(); rate=r;}
    };

} // MUD

#endif //MUD_RECOVER_H
