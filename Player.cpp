//
// Created by Mogician on 2022/5/1.
//


#include "Player.h"
#include "Room.h"
void MUD::Player::Enter(Room *r) {
    currentRoom=r;
    std::cout<<"你进入了"<<currentRoom->ID()<<"号房间。"<<std::endl;
}

int MUD::Player::GetItem(int itemType, int number) {
    if (items[itemType]->Number()+number<0) number=-items[itemType]->Number();
    items[itemType]->Number()+=number;
    return number;
}

void MUD::Player::ShowItems() {
    bool flag= false;
    for (auto o:items) {
        if (o->Number()) flag= true;
    }
    if (!flag){
        std::cout<<"你啥都没有"<<std::endl;
        return;
    }
    std::cout<<"你有："<<std::endl;
    for (auto o:items) {
        if (o->Number()) std::cout<<o->Number()<<"*"<<o->Info()<<"，物品ID："<<o->ItemType()<<std::endl;
    }
}

MUD::Player::Player() {
    for (int i = 0; i < MaxItemCnt; ++i) {
        items[i]=new Item(i);
    }
}
