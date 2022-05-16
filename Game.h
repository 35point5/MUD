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
#include "Telnet.h"

namespace MUD {
    class Generator;

    const int maxMapSize = 20;

class Game: public Telnet::handler {
    private:
        static Timer timer;
        Room *map[maxMapSize][maxMapSize];
        int n, m;
        Room *origin;
        Player *player;
    public:
        Game(Connection<Telnet>& conn): Telnet::handler(conn) {
            GenerateMap();
            Born(conn);
        }

        void GenerateMap();

        void Enter();

        void Leave();

        void Born(Connection <Telnet> &);

        void Handle(std::string op);

        void Move(std::string s);

        void Harvest();

        inline static Timer *GetTimer() { return &timer; }

        void Deposit(int ityoe, int num);

        void Withdraw(int itype, int num);

        void ShowRecipe();
    };

} // MUD

#endif //PROJECT_GAME_H
