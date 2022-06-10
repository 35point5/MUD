//
// Created by Mogician on 2022/6/10.
//

#ifndef MUD_FOOD_H
#define MUD_FOOD_H
#include "Item.h"
namespace MUD {

    class Food: public Item{
        friend class boost::serialization::access;
    private:
        static int foodHeal;
        Food()=default;
    public:
        explicit Food(int num): Item(ItemList::FoodType, num){}

        int Use(Player *p, Room *room, int num) override;

        Item *CopyItem() override;

        template<typename Ar>
        void serialize(Ar &ar, unsigned) {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Item);
        }
    };

} // MUD
BOOST_CLASS_EXPORT_KEY(MUD::Food);
#endif //MUD_FOOD_H
