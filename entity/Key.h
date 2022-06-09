//
// Created by Mogician on 2022/6/9.
//

#ifndef MUD_KEY_H
#define MUD_KEY_H

#include "Item.h"

namespace MUD {

    class Key: public Item{
    private:
        int target;
    public:
        Key(int target,int num): Item(KeyType, num), target(target){};
        bool Use(Player *p, Room *r) override;

        std::string GetInfo() override;
    };

} // MUD

#endif //MUD_KEY_H
