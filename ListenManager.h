//
// Created by root on 5/14/22.
//

#ifndef MUD_LISTENMANAGER_H
#define MUD_LISTENMANAGER_H
#include "ListenSocket.h"
#include "ConnectionManager.h"
namespace MUD {
    template<class protocol,class defaulthandler>
    class ListenManager {
        typedef std::list<ListenSocket*> listenList;
        typedef typename listenList::iterator lListIt;
    protected:
        listenList lList;
        SocketSet sSet;
        ConnectionManager<protocol,defaulthandler> *cm;
    public:
        ~ListenManager(){
            for(auto o:lList){
                o->Close();
                delete o;
            }
        }
        void AddPort(portType port){
            ListenSocket *sock=new ListenSocket;
            sock->Listen(port);
            sock->SetBlock(false);
            lList.push_back(sock);
            sSet.AddSocket(*sock);
        }
        void SwitchConnManager(ConnectionManager<protocol,defaulthandler> *connManager){
            cm=connManager;
        }
        void Listen(){
            DataSocket ds;
            if (!lList.empty() && sSet.Poll()){
                for (auto o:lList){
                    if (sSet.IsAct(*o)){
                        ds=o->Accept();
                        cm->NewConnection(ds);
                    }
                }
            }
        }

    };

} // MUD

#endif //MUD_LISTENMANAGER_H
