//
// Created by Mogician on 2022/6/9.
//

#include "Key.h"
#include "../Room.h"
#include "../Generator.h"
namespace MUD {
    bool Key::Use(Player *p, Room *r) {
        return r->EnableGenerator(target);
    }

    std::string Key::GetInfo() {
        return "key of "+Generator::GeneratorInfo[target];
    }
} // MUD