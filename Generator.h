//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H
#include "Timer.h"
#include "Item.h"
#include "Recover.h"
namespace MUD {
    class Generator {
    private:
        int itemType;
        Recover remain;
        bool disabled;
    public:
        static std::string GeneratorInfo[MaxItemCnt];
        static int DefaultCapacity[MaxItemCnt];
        static int DefaultFrequency[MaxItemCnt];

        Generator(int t, int r = 0, int c = 0, int f = 0);


        int Harvest();

        inline int &Type() {
            return itemType;
        }

        inline int Remain() {
            return remain.Get();
        }

        inline std::string ShowGeneratorInfo() {
            return GeneratorInfo[itemType];
        }
        inline std::string ShowItemInfo(){
            return Item::ItemInfo[itemType];
        }
    };

} // MUD

#endif //PROJECT_GENERATOR_H
