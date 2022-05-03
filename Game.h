//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Entity.h"
#include "Room.h"
#include "Player.h"
#include "Timer.h"
#include "algorithm"
#include "Item.h"
#include "Generator.h"
#include "StringLib.h"

namespace MUD {
    class Generator;

    const int maxMapSize = 20;

    class Game {
    private:
        static Timer timer;
        Room *map[maxMapSize][maxMapSize];
        int n, m;
        Room *origin;
        Player *player;
    public:
        Game() {
            GenerateMap();
            Born();
        }

        void GenerateMap();

        void Born();

        void Run();

        void Move(std::string s);

        void Harvest();
        inline static Timer *GetTimer() { return &timer; }
    };

} // MUD

#endif //PROJECT_GAME_H
