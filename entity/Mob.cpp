//
// Created by Mogician on 2022/6/4.
//

#include "Mob.h"
#include "Dog.h"
#include "Beast.h"
namespace MUD {
    std::vector<Mob*> Mob::Instance{new Dog(),new Beast()};
} // MUD