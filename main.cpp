#include <iostream>
#include "Game.h"
#include "ListenManager.h"
#include "ConnectionManager.h"
#include "glog/logging.h"
#include "glog/raw_logging.h"
using namespace MUD;
int main(int argc, char** argv) {
    FLAGS_logtostderr=1;
    google::InitGoogleLogging(argv[0]);

    ListenManager<Telnet,Game> lm;
    ConnectionManager<Telnet,Game> cm;
    lm.SwitchConnManager(&cm);
    lm.AddPort(23);
    while (true){
        lm.Listen();
        cm.Manage();

    }
    return 0;
}
