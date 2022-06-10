//
// Created by Mogician on 2022/6/9.
//

#ifndef MUD_KEY_H
#define MUD_KEY_H

#include "Item.h"

namespace MUD {

    class Key: public Item{
        friend class boost::serialization::access;
    private:
        int target;
        Key()=default;
    public:
        Key(int target,int num): Item(KeyType, num), target(target){stackable=false;};
        int Use(Player *p, Room *r, int num) override;

        Item *CopyItem() override;

        std::string GetInfo() override;

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Item);
            ar&target;
        }
    };

} // MUD
BOOST_CLASS_EXPORT_KEY(MUD::Key);
#endif //MUD_KEY_H
