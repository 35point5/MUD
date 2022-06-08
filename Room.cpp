//
// Created by Mogician on 2022/5/1.
//

#include "Room.h"
#include "Player.h"
#include "Generator.h"

void MUD::Room::ModifyNeighbour(Room *n, int dir) {
    neighbours[dir] = n;
}

void MUD::Room::AddPlayer(Player *p) {
    players.push_back(p);
}

void MUD::Room::RemovePlayer(int pid) {
    std::vector<Player *>::iterator it;
    for (it = players.begin(); it != players.end(); ++it) {
        if ((*it)->GetID() == pid) {
            players.erase(it);
            break;
        }
    }
}

void MUD::Room::AddGenerator(MUD::Generator *g) {
    generators.push_back(g);
}

std::string MUD::Room::ShowInfo() {
    if (players.empty() && generators.empty() && supplier == nullptr && mobs.empty()) {
//        std::cout << "这里啥都没有。" << std::endl;
        return cyan+"There is nothing.";
    }
    std::stringstream ss;
//    std::cout << "这里有：" << std::endl;
    ss<<green<<"There exists:"<< "\r\n";
    if (supplier != nullptr){
//        std::cout << "仓库" << std::endl;
        ss<<green<<"A supplier."<< "\r\n";
    }
    for (auto o: generators) {
//        std::cout << o->ShowGeneratorInfo() << "，内含" << o->Remain() << "单位" << o->ShowItemInfo() << "。" << std::endl;
        ss<<green<<"A "<<o->ShowGeneratorInfo()<<", contains "<<o->Remain()<<'*'<<o->ShowItemInfo()<<'.'<< "\r\n";
    }
    for(auto o:mobs){
        ss<<red<<"A "<<o->Name()<<" HP:"<<o->GetHP()<<" DMG:"<<o->GetAP()<<".\r\n";
    }
    return ss.str();
}

