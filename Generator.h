//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#include "Timer.h"
#include "entity/Item.h"
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

        explicit Generator(int t, int r = 0, int c = 0, int f = 0);


        int Harvest();

        inline int &Type() {
            return itemType;
        }

        inline int Remain() {
            return disabled?0:remain.Get();
        }

        inline std::string ShowGeneratorInfo() {
            std::stringstream ss;
            if (!disabled)
                ss<<"A "<<GeneratorInfo[itemType]<<", contains "<<Remain()<<'*'<<ShowItemInfo();
            else
                ss<<"A half abandoned "<<GeneratorInfo[itemType];
            return ss.str();
        }

        inline std::string ShowItemInfo() {
            return Item::ItemInfo[itemType];
        }

        inline bool Enable() {
            if (!disabled) return false;
            disabled = false;
            remain.SetVal(0);
            return true;
        }

        inline bool IsDisabled(){return disabled;}
    };

} // MUD

#endif //PROJECT_GENERATOR_H
