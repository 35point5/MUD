//
// Created by Mogician on 2022/6/10.
//

#ifndef MUD_GUN_H
#define MUD_GUN_H
#include "Item.h"
namespace MUD {

    class Gun: public Item{
        friend class boost::serialization::access;
    private:
        static int BulletDamage;
        Gun()=default;
    public:
        explicit Gun(int num): Item(ItemList::GunType, num){}

        int Use(Player *p, Room *room, int num) override;

        Item *CopyItem() override;

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Item);
//            itemType=GunType;
        }
    };

} // MUD
BOOST_CLASS_EXPORT_KEY(MUD::Gun);
#endif //MUD_GUN_H
