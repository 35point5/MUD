//
// Created by Mogician on 2022/5/1.
//

#include "Generator.h"
#include "Game.h"

namespace MUD {
    std::string Generator::GeneratorInfo[MaxItemCnt]={"水井","农场","铁矿"};
    int Generator::DefaultCapacity[MaxItemCnt]={20,10,5};
    int Generator::DefaultFrequency[MaxItemCnt]={10000,30000,60000};
    Generator::Generator(int t, int r, int c, int f) : capacity(c ? c : DefaultCapacity[t]), frequency(f ? f : DefaultFrequency[t]), itemType(t), remain(r), disabled(false) {
        Timer *timer=Game::GetTimer();
        lastTime=timer->TimeTicks();
    }

    void Generator::Update() {
        Timer *timer=Game::GetTimer();
        int duration=timer->TimeTicks()-lastTime;
        remain+=duration/frequency;
        lastTime+=duration/frequency*frequency;
        if (remain>capacity) remain=capacity;
    }

    int Generator::Harvest() {
        Update();
        int r=remain;
        remain=0;
        return r;
    }
} // MUD