//
// Created by Mogician on 2022/6/9.
//

#include "Key.h"
#include "../Room.h"
#include "../Generator.h"
#include "../entity/Player.h"
namespace MUD {

    int Key::Use(Player *p, Room *r, int num) {
        bool flag=r->EnableGenerator(target);
        if (flag) p->Sendln(green+"You use the key to enable the "+Generator::GeneratorInfo[target]+"!");
        else p->Sendln(red+"No such generator!");
        return flag;
    }

    std::string Key::GetInfo() {
        return std::to_string(Number())+"*key of "+Generator::GeneratorInfo[target];
    }

    Item *Key::CopyItem() {
        return new Key(*this);
    }
} // MUD
BOOST_CLASS_EXPORT_IMPLEMENT(MUD::Key);