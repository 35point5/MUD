#include <iostream>
#include "Game.h"
#include "socket/ListenManager.h"
#include "socket/ConnectionManager.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"
#include <unistd.h>
#include "Database.h"
#include "Recover.h"
#include "random"
using namespace MUD;
std::random_device rd;
std::mt19937 mt(rd());
int main(int argc, char** argv) {
    FLAGS_logtostderr=1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO)<<Database::Init()<<std::endl;

    ListenManager<Telnet,Game> lm;
    ConnectionManager<Telnet,Game> cm;
    lm.SwitchConnManager(&cm);
    lm.AddPort(23);
    Game::GenerateMap();
    Recover MobClock(10000);
    while (true){
        lm.Listen();
//        LOG(INFO)<<"listen++"<<std::endl;
        cm.Manage();
//        sleep(1);
//        LOG(INFO)<<"round++"<<std::endl;
        if (MobClock.Get()){
            Game::GenerateMob();
            MobClock.SetVal(0);
        }
    }
    return 0;
}
