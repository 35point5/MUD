//
// Created by Mogician on 2022/5/1.
//


#include "Player.h"
#include "../Room.h"
#include "../Database.h"
#include "../Game.h"
#include "Item.h"
int MUD::Player::DefaultHP=100;
int MUD::Player::DefaultAP=6;
int MUD::Player::DefaultHeal=1000;

void MUD::Player::Enter(Room *r) {
    currentRoom=r;
    if (role>guest){
        std::stringstream ss;
        ss << green << "You entered Field No." << currentRoom->GetID() << "\r\n";
        Sendln(ss.str());
    }
}

void MUD::Player::GetItem(Item* item) {
    if (item->IsStackable()){
        for(auto &o:items) if (o->ItemType()==item->ItemType() && o->IsStackable()){
            o->Number()+=item->Number();
            return;
        }
    }
    items.push_back(item);
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
    int index=0;
    for (auto o:items) {
        ss<<green<<o->GetInfo()<<", item Index:"<<index<<"\r\n";
        ++index;
    }
    return ss.str();
}

MUD::Player::Player(Connection<Telnet> &c): Creature(DefaultHeal,DefaultHP,DefaultAP), role(guest){
    conn=&c;
    name=c.IP();
}

void MUD::Player::Sendln(const std::string &s) {
    conn->SendString(s+newline);
}

MUD::Player::~Player() {
    if (role<=guest) return;
    auto s=SerializeTo();
    currentRoom->RemovePlayer(id);
    for(auto o:items) delete o;
    LOG(INFO)<<"serialization: "<<s<<std::endl;
    Save(s);
}

bool MUD::Player::PlayerExist(const std::string &name) {
    return Database::FindPlayer.store(name).num_rows();
}

void MUD::Player::Save(const std::string &info) {
    if (PlayerExist(name)){
        Database::UpdatePlayer.execute(name,password,info,name);
    }
    else{
        Database::InsertPlayer.execute(name,password,info);
    }
}

mysqlpp::StoreQueryResult MUD::Player::FindPlayer(const std::string &name) {
    return Database::FindPlayer.store(name);
}

MUD::Player *MUD::Player::Create(const std::string &ar, Connection <Telnet> &conn) {
    std::stringstream ss(ar);
    boost::archive::text_iarchive ia(ss);
    Player *p=new Player(conn);
    ia>>*p;
    return p;
}

bool MUD::Player::AuthPlayer(const std::string &name, const std::string &password) {
    return Database::AuthPlayer.store(name,password).num_rows();
}

bool MUD::Player::Register(const std::string &p_name, const std::string &p_password) {
    if (PlayerExist(p_name)){
        Sendln(red+"Player already exists!");
        return false;
    }
    if (!p_name.length() || p_name.length() > 18){
        Sendln(red+"Invalid p_name length!");
        return false;
    }
    if (!p_password.length() || p_password.length() > 18){
        Sendln(red+"Invalid p_password length!");
        return false;
    }
    role=common;
    name=p_name;
    password=p_password;
    Save(SerializeTo());
    Sendln("Welcome to this wasteland, whether this place will be the beginning of human-beings, or be the end of this kind, it is now, all depend on you...");
    Sendln("You used to be very familiar with this fair land, but the shattered moon light, the broken landscape bring you back to reality...");
    Sendln("But drag your attention back here for a moment, you need to learn to live in this hell. Try thinking about \"help\", there might be some knowledge occur to you.");
    Sendln(currentRoom->ShowInfo());
    return true;
}

std::string MUD::Player::SerializeTo() {
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa<<*this;
    return ss.str();
}

bool MUD::Player::Login(const std::string &p_name, const std::string &p_password) {
    if (!PlayerExist(p_name)){
        Sendln(red+"Player doesn't exist!");
        return false;
    }
    if (!AuthPlayer(p_name,p_password)){
        Sendln(red+"Invalid name or password!");
        return false;
    }
    auto res= FindPlayer(p_name);
    auto row=*res.begin();
    UnserializeFrom(row["info"].c_str());
    Sendln(currentRoom->ShowInfo());
    return true;
}

void MUD::Player::UnserializeFrom(const std::string &s) {
    std::stringstream ss(s);
    boost::archive::text_iarchive ia(ss);
    ia>>*this;
}


void MUD::Player::Deathrattle(MUD::Room *cur_room, MUD::Creature *) {
    cur_room->RemovePlayer(id);
    Enter(Game::origin);
    Sendln(Game::origin->ShowInfo());
    Game::origin->AddPlayer(this);
}

int MUD::Player::RemoveItem(int itemType, int number) {
    for (auto it=items.begin();it!=items.end();){
        if ((*it)->ItemType()==itemType){
            if ((*it)->Number()>number){
                (*it)->Number()-=number;
                return 0;
            }
            number-=(*it)->Number();
            delete (*it);
            it=items.erase(it);
            continue;
        }
        ++it;
    }
    return number;
}

MUD::Item * MUD::Player::FetchItem(int itemIndex) {
    if (itemIndex>=items.size()) return nullptr;
    auto res=items[itemIndex];
    items.erase(items.begin()+itemIndex);
    return res;
}

int MUD::Player::ItemCnt(int id) {
    int num=0;
    for(auto o:items) if (o->ItemType()==id) num+=o->Number();
    return num;
}

void MUD::Player::Use(int index, int num) {
    if (index>=items.size() || num<=0){
        Sendln(red+"No such item!");
        return;
    }
    if (items[index]->Number()<num){
        Sendln(red+"No enough items!");
        return;
    }
    int used= items[index]->Use(this, currentRoom, num);
    if (used) Sendln(green+"You used "+ std::to_string(used)+"*"+items[index]->Info()+"!");
    items[index]->Number()-=used;
    if (items[index]->Number()<=0){
        delete items[index];
        items.erase(items.begin()+index);
    }
}
