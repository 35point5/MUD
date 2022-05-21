//
// Created by Mogician on 2022/5/1.
//


#include "Player.h"
#include "Room.h"
void MUD::Player::Enter(Room *r) {
    currentRoom=r;
    std::stringstream ss;
    ss << green << "You entered room No." << currentRoom->GetID() << "\r\n";
    Sendln(ss.str());
}

int MUD::Player::GetItem(int itemType, int number) {
    if (items[itemType]->Number()+number<0) number=-items[itemType]->Number();
    items[itemType]->Number()+=number;
    return number;
}

std::string MUD::Player::ShowItems() {
    bool flag= false;
    std::stringstream ss;
    for (auto o:items) {
        if (o->Number()) flag= true;
    }
    if (!flag){
        return cyan+"You have nothing.";
    }
    ss<<green<<"You have:"<<"\r\n";
    for (auto o:items) {
        if (o->Number()) ss<<green<<o->Number()<<"*"<<o->Info()<<", item GetID:"<<o->ItemType()<<"\r\n";
    }
    return ss.str();
}

MUD::Player::Player(Connection<Telnet> &c) {
    conn=&c;
    name=c.IP();
    for (int i = 0; i < MaxItemCnt; ++i) {
        items[i]=new Item(i);
    }
}

void MUD::Player::Sendln(std::string s) {
    conn->SendString(s+newline);
}
