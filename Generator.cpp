//
// Created by Mogician on 2022/5/1.
//

#include "Generator.h"
#include "Game.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"
namespace MUD {
    std::string Generator::GeneratorInfo[MaxItemCnt]={"well","farm","mine"};
    int Generator::DefaultCapacity[MaxItemCnt]={20,10,5};
    int Generator::DefaultFrequency[MaxItemCnt]={10,30,60};
    Generator::Generator(int t, int r, int c, int f) : capacity(c ? c : DefaultCapacity[t]), frequency(f ? f : DefaultFrequency[t]), itemType(t), remain(r), disabled(false) {
        Timer *timer=Game::GetTimer();
        lastTime=timer->TimeS();
    }

    void Generator::Update() {
        Timer *timer=Game::GetTimer();
        long long duration=timer->TimeS()-lastTime;
        LOG(INFO)<<duration<<std::endl;
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