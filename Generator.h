//
// Created by Mogician on 2022/5/1.
//
#include "Timer.h"
#include "Item.h"

#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

namespace MUD {
    class Generator {
    private:
        int capacity;
        int frequency;
        int itemType;
        int remain;
        int lastTime;
        bool disabled;
    public:
        static std::string GeneratorInfo[MaxItemCnt];
        static int DefaultCapacity[MaxItemCnt];
        static int DefaultFrequency[MaxItemCnt];

        Generator(int t, int r = 0, int c = 0, int f = 0);

        void Update();

        int Harvest();

        inline int &Type() {
            Update();
            return itemType;
        }

        inline int &Remain() {
            Update();
            return remain;
        }

        inline std::string ShowGeneratorInfo() {
            Update();
            return GeneratorInfo[itemType];
        }
        inline std::string ShowItemInfo(){
            Update();
            return Item::ItemInfo[itemType];
        }
    };

} // MUD

#endif //PROJECT_GENERATOR_H
