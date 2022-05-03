//
// Created by Mogician on 2022/5/1.
//

#include <fstream>
#include "Game.h"

namespace MUD {
    Timer Game::timer;

    void Game::GenerateMap() {
        std::ifstream is;
        is.open("map.data", std::ios::in);
        std::string s;
        for (n = 0; n < maxMapSize; ++n) {
            if (!(is >> s)) break;
            for (m = 0; m < s.length(); ++m) {
                map[n][m] = new Room;
                if (s[m] == 'O') origin = map[n][m];
            }
        }
        std::cout << "size:" << n << ' ' << m << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i) map[i][j]->ModifyNeighbour(map[i - 1][j], North);
                if (j) map[i][j]->ModifyNeighbour(map[i][j - 1], West);
                if (i < maxMapSize - 1) map[i][j]->ModifyNeighbour(map[i + 1][j], South);
                if (j < maxMapSize - 1) map[i][j]->ModifyNeighbour(map[i][j + 1], East);
            }
        }
        Generator *W= new Generator(Water,3);
        origin->AddGenerator(W);
        Generator *S= new Generator(Food,1);
        origin->AddGenerator(S);
        Generator *M= new Generator(Metal);
        origin->AddGenerator(M);
        Supplier *Sup=new Supplier;
        origin->ModifySupplier(Sup);
    }

    void Game::Born() {
        player = new Player;
        player->Enter(origin);
        origin->ShowInfo();
        origin->AddPlayer(player);
    }

    void Game::Run() {
        std::string op;
        StringVec sv;
        while (true) {
            std::getline(std::cin, op);
            std::transform(op.begin(), op.end(), op.begin(), ::tolower);
            sv = split(op);
            //for (auto o: sv) std::cout << o << std::endl;
            if (sv[0] == "move") {
                Move(sv[1]);
            } else if (sv[0] == "harvest") {
                Harvest();
            }
            else if (sv[0]=="refresh"){
                player->CurrentRoom()->ShowInfo();
            }
            else if (sv[0]=="bag"){
                player->ShowItems();
            }

        }
    }

    void Game::Move(std::string s) {
        int dir;
        if (s == "e") dir = 0;
        else if (s == "s") dir = 1;
        else if (s == "w") dir = 2;
        else if (s == "n") dir = 3;
        else {
            std::cout << "无效指令!" << std::endl;
            return;
        }
        Room *cur = player->CurrentRoom();
        Room *nxt = cur->GetNeighbour(dir);
        if (nxt == nullptr) {
            std::cout << "此路不通" << std::endl;
            return;
        }
        cur->RemovePlayer(player->ID());
        player->Enter(nxt);
        nxt->ShowInfo();
        nxt->AddPlayer(player);
    }

    void Game::Harvest() {
        Room *cur = player->CurrentRoom();
        std::cout << "您获得了：" << std::endl;
        int hnum, htype;
        for (auto o: cur->GetGenerator()) {
            htype = o->Type();
            hnum = o->Harvest();
            std::cout<<hnum<<'*'<<o->ShowItemInfo()<<std::endl;
            player->GetItem(htype, hnum);
        }
    }
} // MUD