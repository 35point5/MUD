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
#include "fstream"

namespace MUD {
    class Generator;

    const int maxMapSize = 20;

    class Game : public Telnet::handler {
    private:
        static Timer timer;
        static Room map[maxMapSize][maxMapSize];
        static int n, m;
        Player *player;
    public:
        static Room *origin;
        Game(Connection<Telnet> &conn) : Telnet::handler(conn) {
            Born(conn);
        }
        ~Game();
        static void GenerateMap();

        void Enter();

        void Leave();

        void Born(Connection<Telnet> &);

        void Handle(std::string op);

        void Move(std::string s);

        void Harvest();

        inline static Timer *GetTimer() { return &timer; }

        void Deposit(int itype);

        void Withdraw(int itype);

        void ShowRecipe();

        void Craft(int id, int num);

        void Status();

        void Momomo();
    };

} // MUD

#endif //PROJECT_GAME_H
