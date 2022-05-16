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
        Generator *W = new Generator(Water, 3);
        origin->AddGenerator(W);
        Generator *S = new Generator(Food, 1);
        origin->AddGenerator(S);
        Generator *M = new Generator(Metal);
        origin->AddGenerator(M);
        Supplier *Sup = new Supplier;
        origin->ModifySupplier(Sup);
    }

    void Game::Born(Connection <Telnet> &conn) {
        player = new Player(conn);
        player->Enter(origin);
        player->Sendln(origin->ShowInfo());
        origin->AddPlayer(player);
    }

    void Game::Handle(std::string op) {
        StringVec sv;
        std::transform(op.begin(), op.end(), op.begin(), ::tolower);
        sv = split(op);
        //for (auto o: sv) std::cout << o << std::endl;
        if (sv[0] == "move") {
            Move(sv[1]);
        } else if (sv[0] == "harvest") {
            Harvest();
        } else if (sv[0] == "refresh") {
            player->Sendln(player->CurrentRoom()->ShowInfo());
        } else if (sv[0] == "bag") {
            player->ShowItems();
        } else if (sv[0] == "deposit") {
            Deposit(std::stoi(sv[1]), std::stoi(sv[2]));
        } else if (sv[0] == "withdraw") {
            Withdraw(std::stoi(sv[1]), std::stoi(sv[2]));
        }else if (sv[0]=="recipe"){
            ShowRecipe();
        }

    }

    void Game::Move(std::string s) {
        int dir;
        if (s == "e") dir = 0;
        else if (s == "s") dir = 1;
        else if (s == "w") dir = 2;
        else if (s == "n") dir = 3;
        else {
//            std::cout<<"无效指令"<<std::endl;
            player->Sendln(red+"Invalid command!");
            return;
        }
        Room *cur = player->CurrentRoom();
        Room *nxt = cur->GetNeighbour(dir);
        if (nxt == nullptr) {
//            std::cout << "There is no way out!" << std::endl;
            player->Sendln(red+"There is no way out!");
            return;
        }
        cur->RemovePlayer(player->ID());
        player->Enter(nxt);
        player->Sendln(nxt->ShowInfo());
        nxt->AddPlayer(player);
    }

    void Game::Harvest() {
        Room *cur = player->CurrentRoom();
//        std::cout << "You get:" << std::endl;
        std::stringstream ss;
        ss<<green+"You've got:"<<"\r\n";
        int hnum, htype;
        for (auto o: cur->GetGenerator()) {
            htype = o->Type();
            hnum = o->Harvest();
//            std::cout << hnum << '*' << o->ShowItemInfo() << std::endl;
            ss<<green+std::to_string(hnum)+'*'+o->ShowItemInfo()<<"\r\n";
            player->GetItem(htype, hnum);
        }
        player->Sendln(ss.str());
    }

    void Game::Deposit(int itype, int num) {
        num = -player->GetItem(itype, -num);
        player->CurrentRoom()->GetSupplier()->Deposit(itype, num);
//        std::cout << "You deposit: " << num << "*" << Item::ItemInfo[itype] << std::endl;
        player->Sendln(green+"You've deposited: "+ std::to_string(num)+'*'+Item::ItemInfo[itype]);
    }

    void Game::Withdraw(int itype, int num) {
        num = player->CurrentRoom()->GetSupplier()->Withdraw(itype, num);
        player->GetItem(itype, num);
//        std::cout << "你从仓库中取出了" << num << "*" << Item::ItemInfo[itype] << std::endl;
        player->Sendln(green+"You've withdrawn: "+ std::to_string(num)+'*'+Item::ItemInfo[itype]);
    }

    void Game::Enter() {
        std::cout << "Hello!" << std::endl;
    }

    void Game::Leave() {
        std::cout << "Bye!" << std::endl;
    }

    void Game::ShowRecipe() {
        std::stringstream ss;
        int cnt=0;
        for (int i=0;i<RecipeCnt;++i){
            bool flag=true;
            for (int j=0;j<MaxItemCnt;++j){
                if (Recipe[i][j] && !player->ItemCnt(j)){
                    flag=false;
                    break;
                }
            }
            if (flag){
                if (!cnt++) ss<<green<<"Recipes:"<<"\r\n";
                ss<<green;
                for (int j=0;j<MaxItemCnt;++j){
                    if (Recipe[i][j]) ss<<Recipe[i][j]<<"*"<<Item::ItemInfo[j]<<" ";
                }
                ss<<"-->";
                for (int j=0;j<MaxItemCnt;++j){
                    if (Product[i][j]) ss<<Product[i][j]<<"*"<<Item::ItemInfo[j]<<" ";
                }
                ss<<"\r\n";
            }
        }
        if (!cnt) ss<<cyan<<"No available recipe now!";
        player->Sendln(ss.str());
    }

} // MUD