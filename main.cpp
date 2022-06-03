#include <iostream>
#include "Game.h"
#include "ListenManager.h"
#include "ConnectionManager.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"
#include <unistd.h>
#include "Database.h"
using namespace MUD;
int main(int argc, char** argv) {
    FLAGS_logtostderr=1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO)<<Database::Init()<<std::endl;

    ListenManager<Telnet,Game> lm;
    ConnectionManager<Telnet,Game> cm;
    lm.SwitchConnManager(&cm);
    lm.AddPort(23);
    Game::GenerateMap();
    while (true){
        lm.Listen();
//        LOG(INFO)<<"listen++"<<std::endl;
        cm.Manage();
//        sleep(1);
//        LOG(INFO)<<"round++"<<std::endl;
    }
    return 0;
}
