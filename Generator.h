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
        Item *item;
        Recover remain;
        bool disabled;
    public:
        static std::string GeneratorInfo[MaxItemCnt];
        static int DefaultCapacity[MaxItemCnt];
        static int DefaultFrequency[MaxItemCnt];

        explicit Generator(Item* t, int r = 0, int c = 0, int f = 0);


        Item * Harvest();

        inline int Type() {
            return item->ItemType();
        }

        inline int Remain() {
            return disabled?0:remain.Get();
        }

        inline std::string ShowGeneratorInfo() {
            std::stringstream ss;
            if (!disabled)
                ss<<"A "<<GeneratorInfo[Type()]<<", contains "<<Remain()<<'*'<<ShowItemInfo();
            else
                ss<<"A half abandoned "<<GeneratorInfo[Type()];
            return ss.str();
        }

        inline std::string ShowItemInfo() {
            return Item::ItemInfo[Type()];
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
