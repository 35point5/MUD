//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

namespace MUD {
//    const int Water = 0;
//    const int Food = 1;
//    const int Metal = 2;
//    const int Wood = 3;
//    const int Gunpowder=4;
    enum ItemList {
        Water = 0,
        Food,
        Metal,
        Wood,
        Gunpowder,
        KeyOfFarm,
        KeyOfBlastFurnance,
        CallerToTheSun,
        TheReconstructor,
        Sword,
        Gun,
        Bullet
    };
    const int MaxItemCnt = 20;

    class Item {
        friend class boost::serialization::access;

    private:
        int itemType;
        int number;
    public:
        Item(int t=-1, int num=0);

        static std::string ItemInfo[MaxItemCnt];

        inline int &ItemType() { return itemType; }

        inline int &Number() { return number; }

        inline std::string Info() { return ItemInfo[itemType]; }

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & itemType;
            ar & number;
        }
    };

} // MUD

#endif //PROJECT_ITEM_H
