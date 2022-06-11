//
// Created by Mogician on 2022/5/1.
//


#include "Game.h"
#include "entity/Food.h"

namespace MUD {
    Timer Game::timer;
    Room Game::map[maxMapSize][maxMapSize];
    int Game::n;
    int Game::m;
    Room *Game::origin;
    int Game::maxMob = 3;

    void Game::Born(Connection<Telnet> &conn) {
        player = new Player(conn);
        player->Enter(origin);
        player->Sendln(green + "Welcome! Please register or login first.");
//        player->ClearBuf();
//        std::cout<<"Canceled"<<std::endl;
        origin->AddPlayer(player);
    }

    void Game::Handle(std::string op) {
        if (!op.length()) return;
        StringVec sv;
        std::transform(op.begin(), op.end(), op.begin(), ::tolower);
        sv = split(op);
        //for (auto o: sv) std::cout << o << std::endl;

        try {
            if (player->GetRole() == guest) {
                if (sv[0] == "register") {
                    player->Register(sv.at(1), sv.at(2));
                } else if (sv[0] == "login") {
                    player->Login(sv.at(1), sv.at(2));
                }
            } else {
                if (sv[0] == "move") {
                    Move(sv.at(1));
                } else if (sv[0] == "harvest") {
                    Harvest();
                } else if (sv[0] == "refresh") {
                    player->Sendln(
                            "You check the supplier once more, seeing the resources comming out from supplier makes you satisfied.");
                    player->Sendln(player->CurrentRoom()->ShowInfo());
                } else if (sv[0] == "bag") {
                    player->Sendln(dim + cyan + "You check your bag to see whether there is something you can use.");
                    player->Sendln(player->ShowItems());
                } else if (sv[0] == "status") {
                    Status();
                } else if (sv[0] == "deposit") {
                    Deposit(std::stoi(sv.at(1)));
                } else if (sv[0] == "withdraw") {
                    Withdraw(std::stoi(sv.at(1)));
                } else if (sv[0] == "recipe") {
                    ShowRecipe();
                } else if (sv[0] == "craft") {
                    Craft(std::stoi(sv.at(1)), std::stoi(sv.at(2)));
                } else if (sv[0] == "battle") {
                    Battle();
                } else if (sv[0] == "pickup") {
                    Pickup();
                } else if (sv[0] == "supplier") {
                    ShowSupplier();
                } else if (sv[0] == "use") {
                    Use(std::stoi(sv.at(1)), std::stoi(sv.at(2)));
                } else if (sv[0] == "help") {
                    Help();
                } else if (sv[0] == "momomo") {
                    Momomo();
                } else player->InvalidCommand();
            }

        } catch (...) { player->InvalidCommand(); }

    }

    void Game::Help() {
        std::stringstream ss;
        ss << green << "move e/w/n/s" << newline;
        ss << green << "harvest" << newline;
        ss << green << "refresh" << newline;
        ss << green << "bag" << newline;
        ss << green << "status" << newline;
        ss << green << "deposit index" << newline;
        ss << green << "withdraw index" << newline;
        ss << green << "recipe" << newline;
        ss << green << "craft ID number" << newline;
        ss << green << "battle" << newline;
        ss << green << "pickup" << newline;
        ss << green << "supplier" << newline;
        ss << green << "use index number" << newline;
        player->Sendln(ss.str());
    }

    void Game::Move(std::string s) {
        int dir;
        if (s == "e") dir = 0;
        else if (s == "s") dir = 1;
        else if (s == "w") dir = 2;
        else if (s == "n") dir = 3;
        else {
//            std::cout<<"无效指令"<<std::endl;
            player->InvalidCommand();
            return;
        }
        Room *cur = player->CurrentRoom();
        Room *nxt = cur->GetNeighbour(dir);
        if (nxt == nullptr) {
//            std::cout << "There is no way out!" << std::endl;
            player->Sendln(red + "There is no way out!");
            return;
        }
        cur->RemovePlayer(player->GetID());
        player->Enter(nxt);
        player->Sendln(nxt->ShowInfo());
        nxt->AddPlayer(player);
    }

    void Game::Harvest() {
        Room *cur = player->CurrentRoom();
//        std::cout << "You get:" << std::endl;
        std::stringstream ss;
        std::vector<Item *> vec;
        for (auto o: cur->GetGenerator()) {
            auto harItem = o->Harvest();
            if (harItem != nullptr) vec.push_back(harItem);
//            std::cout << hnum << '*' << o->ShowItemInfo() << std::endl;
        }
        if (vec.empty()) ss << cyan + dim + "Nothing to harvest." << newline;
        else {
            ss << dim + cyan + "You take the resources into your bag, so what's the next step?" << newline;
            ss << green + "You've got:" << newline;
            for (auto o: vec) {
                ss << green + o->GetInfo() << newline;
                player->GetItem(o);
            }
        }
        player->Sendln(ss.str());
    }

    void Game::Deposit(int index) {
        auto item = player->FetchItem(index);
        player->CurrentRoom()->GetSupplier()->Deposit(item);
//        std::cout << "You deposit: " << num << "*" << Item::ItemInfo[itype] << std::endl;
        player->Sendln(green + "You've deposited: " + item->GetInfo() +
                       ", you don't need it in your bag any more.");
    }

    void Game::Withdraw(int index) {
        auto item = player->CurrentRoom()->GetSupplier()->Withdraw(index);
        if (item == nullptr) {
            player->Sendln(red + "No such item!");
            return;
        }
        player->GetItem(item);
//        std::cout << "你从仓库中取出了" << num << "*" << Item::ItemInfo[index] << std::endl;
        player->Sendln(green + "You've withdrawn: " + item->GetInfo() +
                       ", they are now in your bag.");
    }

    void Game::Enter() {
        std::cout << "Hello!" << std::endl;
    }

    void Game::Leave() {
        std::cout << "Bye!" << std::endl;
    }

    void Game::ShowRecipe() {
        std::stringstream ss;
        ss << cyan + dim << "You think you can take advantage of the things you have." << newline;
        int cnt = 0;
        for (int i = 0; i < RecipeCnt; ++i) {
            bool flag = true;
            for (int j = 0; j < MaxItemCnt; ++j) {
                if (Recipe[i][j] && !player->ItemCnt(j)) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                if (!cnt++) ss << green << "Recipes:" << "\r\n";
                ss << green;
                for (int j = 0; j < MaxItemCnt; ++j) {
                    if (Recipe[i][j]) ss << Recipe[i][j] << "*" << Item::ItemInfo[j] << " ";
                }
                ss << "-->";
                for (auto o: Product[i]) ss << o->GetInfo() << " ";
                ss << "(ID:" << i << ")\r\n";
            }
        }
        if (!cnt) ss << cyan << "No available recipe now!";
        player->Sendln(ss.str());
    }

    void Game::Momomo() {
        for (int i = 0; i < MaxItemCnt; ++i) player->GetItem(new Item(i, 999));
    }

    void Game::Craft(int id, int num) {
        bool flag = true;
        for (int i = 0; i < MaxItemCnt; ++i) {
            if (Recipe[id][i] * num > player->ItemCnt(i)) {
                flag = false;
                break;
            }
        }
        std::stringstream ss;
        if (flag) {
            ss << green << "You consumed ";
            for (int i = 0; i < MaxItemCnt; ++i)
                if (Recipe[id][i]) {
//                    player->GetItem(i, -num * Recipe[id][i]);
                    player->RemoveItem(i, num * Recipe[id][i]);
                    ss << num * Recipe[id][i] << "*" << Item::ItemInfo[i] << " ";
                }
            ss << "\r\n" << green << "And got ";
            for (auto o: Product[id]) {
                auto newItem = o->CopyItem();
                newItem->Number() *= num;
                player->GetItem(newItem);
                ss << newItem->GetInfo() << " ";
            }
        } else ss << red << "Insufficient materials.";
        player->Sendln(ss.str());
    }

    void Game::GenerateMap() {
        std::ifstream is;
        is.open("map.data", std::ios::in);
        std::string s;
        for (n = 0; n < maxMapSize; ++n) {
            if (!(is >> s)) break;
            for (m = 0; m < s.length(); ++m) {
                if (s[m] == 'O') {
                    origin = &map[n][m];
                    map[n][m].SetLevel(-1);
                } else map[n][m].SetLevel(s[m] - '0');
            }
        }
        std::cout << "size:" << n << ' ' << m << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i) map[i][j].ModifyNeighbour(&map[i - 1][j], North);
                if (j) map[i][j].ModifyNeighbour(&map[i][j - 1], West);
                if (i < n - 1) map[i][j].ModifyNeighbour(&map[i + 1][j], South);
                if (j < m - 1) map[i][j].ModifyNeighbour(&map[i][j + 1], East);
            }
        }
        Generator *W = new Generator(new Item(Water, 1), 3);
        origin->AddGenerator(W);
        Generator *S = new Generator(new Food(1), 1);
        origin->AddGenerator(S);
        Generator *M = new Generator(new Item(Metal, 1));
        origin->AddGenerator(M);
        Supplier *Sup = new Supplier;
        origin->ModifySupplier(Sup);
    }

    Game::~Game() {
        delete player;
    }

    void Game::Status() {
        player->Sendln(
                cyan + "HP: " + std::to_string(player->GetHP()) + "/" + std::to_string(player->MaxHP()) + "    AP: " +
                std::to_string(player->GetAP()));
        player->Sendln(player->ShowItems());
    }

    void Game::GenerateMob() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (map[i][j].GetMobCnt() < Game::maxMob && map[i][j].GetLevel() >= 0) {
                    map[i][j].AddMob(Mob::Instance[map[i][j].GetLevel()]->CopyMob());
                }
    }

    void Game::Battle() {
        auto &mobs = player->CurrentRoom()->GetMobs();
        while (1) {
            if (mobs.empty()) break;
            if (player->Attack(*mobs.back())) {
                mobs.back()->Deathrattle(player->CurrentRoom(), player);
                delete mobs.back();
                mobs.pop_back();
            }
            for (auto o: mobs) {
                if (o->Attack(*player)) {
                    player->Deathrattle(player->CurrentRoom(), o);
                    return;
                }
            }
        }
    }

    void Game::Pickup() {
        auto &items = player->CurrentRoom()->GetItems();
        while (!items.empty()) {
            player->GetItem(items.back());
            player->Sendln(green + "You get " + (items.back())->GetInfo() + ".");
            items.pop_back();
        }
    }

    void Game::ShowSupplier() {
        player->Sendln(player->CurrentRoom()->GetSupplier()->ShowInfo());
    }

    void Game::Use(int index, int num) {
        player->Use(index, num);
    }


} // MUD