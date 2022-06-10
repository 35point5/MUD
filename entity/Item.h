//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include "boost/serialization/base_object.hpp"
#include "boost/serialization/export.hpp"
#include "boost/serialization/access.hpp"

namespace MUD {
//    const int Water = 0;
//    const int FoodType = 1;
//    const int Metal = 2;
//    const int Wood = 3;
//    const int Gunpowder=4;
    enum ItemList {
        Water = 0,
        FoodType,
        Metal,
        Wood,
        Gunpowder,
        KeyType,
        KeyOfBlastFurnance,
        CallerToTheSun,
        TheReconstructor,
        Sword,
        GunType,
        Bullet
    };
    const int MaxItemCnt = 20;

    class Room;

    class Player;

    class Item {
        friend class boost::serialization::access;

    protected:
        int itemType;
        int number;
        int stackable;

    public:
        Item(int t = -1, int num = 0);

        static std::string ItemInfo[MaxItemCnt];

        inline int &ItemType() { return itemType; }

        inline int &Number() { return number; }

        inline std::string Info() { return ItemInfo[itemType]; }

        virtual int Use(Player *p, Room *, int num);

        virtual std::string GetInfo() { return std::to_string(number) + "*" + ItemInfo[itemType]; }

        virtual Item *CopyItem() { return new Item(*this); };

        inline bool IsStackable() { return stackable; }

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & itemType;
            ar & number;
            ar & stackable;
        }
    };

} // MUD

#endif //PROJECT_ITEM_H
