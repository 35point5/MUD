//
// Created by Mogician on 2022/5/1.
//
#include "vector"
#include "Entity.h"
#include "Supplier.h"
#include "sstream"
#include "Mob.h"

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
    class Room: public Entity{
    private:
        std::vector<Player*> players;
        Room *neighbours[MaxDirection];
        std::vector<Generator*> generators;
        Supplier *supplier;
        std::vector<Mob*> mobs;
    public:
        void ModifyNeighbour(Room *n, int dir);
        void AddPlayer(Player *p);
        void RemovePlayer(int pid);
        void AddGenerator(Generator *g);
        std::string ShowInfo();
        inline void ModifySupplier(Supplier *s){supplier=s;}
        inline Room *GetNeighbour(int d){return neighbours[d];};
        inline std::vector<Generator*> &GetGenerator(){return generators;}
        inline Supplier *GetSupplier(){return supplier;}
        inline int GetMobCnt(){return mobs.size();}
        inline void AddMob(Mob *mob){mobs.push_back(mob);}
        inline std::vector<Mob*> &GetMobs(){return mobs;}
    };

}

#endif //PROJECT_ROOM_H
