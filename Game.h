//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "entity/Entity.h"
#include "Room.h"
#include "entity/Player.h"
#include "Timer.h"
#include "algorithm"
#include "entity/Item.h"
#include "Generator.h"
#include "StringLib.h"
#include "socket/Telnet.h"
#include "fstream"
#include "entity/Dog.h"

namespace MUD {
    class Generator;

    const int maxMapSize = 20;

    class Game : public Telnet::handler {
    private:
        static Timer timer;
        static Room map[maxMapSize][maxMapSize];
        static int n, m;
        static int maxMob;
        Player *player;
    public:
        static Room *origin;
        Game(Connection<Telnet> &conn) : Telnet::handler(conn) {
            Born(conn);
        }
        ~Game();
        static void GenerateMap();

        static void GenerateMob();

        void Enter();

        void Leave();

        void Born(Connection<Telnet> &);

        void Handle(std::string op);

        void Move(std::string s);

        void Harvest();

        inline static Timer *GetTimer() { return &timer; }

        void Deposit(int itype);

        void Withdraw(int index);

        void ShowRecipe();

        void Craft(int id, int num);

        void Status();

        void Battle();

        void Pickup();

        void ShowSupplier();

        void Use(int index, int num);

        void Help();

        void Momomo();
    };

} // MUD

#endif //PROJECT_GAME_H
