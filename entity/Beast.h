//
// Created by Mogician on 2022/6/10.
//

#ifndef MUD_BEAST_H
#define MUD_BEAST_H
#include "Mob.h"
namespace MUD {

    class Item;
    class Beast: public Mob{
    private:
        static std::vector<std::pair<Item *, int>> drop;
    public:
        Beast(int r = 3000, int h = 15, int a = 4) : Mob(r, h, a) { name = "Beast"; description="A huge creature. They are strong, maybe stronger in the past. But now, you can deal with it with your strength.";}

        void Deathrattle(Room *room, Creature *creature) override;

        Mob *CopyMob() override;
    };

} // MUD

#endif //MUD_BEAST_H
