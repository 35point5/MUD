//
// Created by Mogician on 2022/5/1.
//
#include "vector"
#include "entity/Entity.h"
#include "Supplier.h"
#include "sstream"
#include "entity/Mob.h"
#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

namespace MUD{
    class Player;
    class Generator;
    const int MaxDirection=4;
    const char Direction[MaxDirection]={'e','s','w','n'};
    const int East=0;
    const int South=1;
    const int West=2;
    const int North=3;
    const std::vector<std::string> RoomInfo={"There exists a kind of weak creature, they are starved, they have no fear.","There exists a huge creature. They are strong, maybe stronger in the past. But now, you can deal with it with your strength."};
    class Room: public Entity{
    private:
        std::vector<Player*> players;
        Room *neighbours[MaxDirection];
        std::vector<Generator*> generators;
        Supplier *supplier;
        std::vector<Mob*> mobs;
        std::vector<Item*> items;
        int level;
    public:
        void ModifyNeighbour(Room *n, int dir);
        void AddPlayer(Player *p);
        void RemovePlayer(int pid);
        void AddGenerator(Generator *g);
        bool EnableGenerator(int gid);
        std::string ShowInfo();
        inline void ModifySupplier(Supplier *s){supplier=s;}
        inline Room *GetNeighbour(int d){return neighbours[d];};
        inline std::vector<Generator*> &GetGenerator(){return generators;}
        inline Supplier *GetSupplier(){return supplier;}
        inline int GetMobCnt(){return mobs.size();}
        inline void AddMob(Mob *mob){mobs.push_back(mob);}
        inline std::vector<Mob*> &GetMobs(){return mobs;}
        inline void AddItem(Item *it){items.push_back(it);}
        inline std::vector<Item*>& GetItems(){return items;}
        inline void SetLevel(int l){level=l;}
        inline int GetLevel(){return level;}
    };

}

#endif //PROJECT_ROOM_H
