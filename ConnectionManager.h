//
// Created by root on 5/14/22.
//

#ifndef MUD_CONNECTIONMANAGER_H
#define MUD_CONNECTIONMANAGER_H
#include "list"
#include "Connection.h"
#include "SocketSet.h"
namespace MUD {
    template<class protocol,class defaultHandler>
    class ConnectionManager {
        typedef std::list<Connection<protocol>*> connList;
        typedef typename connList::iterator cListIt;
    protected:
        connList cList;
        SocketSet sSet;
    public:
        ~ConnectionManager(){
            for(cListIt it=cList.begin(); it != cList.end(); ++it){
                (*it)->CloseSocket();
                delete (*it);
            }
        }
        void NewConnection(const DataSocket& sock){
            Connection<protocol> *conn=new Connection<protocol>(sock);
            cList.push_back(conn);
            conn->SetBlock(false);
            conn->SwitchHandler(new defaultHandler(*conn));
            sSet.AddSocket(*conn);
        }
        void Close(cListIt &it){
            sSet.RemoveSocket(**it);
            (*it)->CloseSocket();
            it=cList.erase(it);
        }
        void Listen(){
            if (!cList.empty() && sSet.Poll()){
                for (cListIt it=cList.begin();it!=cList.end();){
                    if (sSet.IsAct(**it)){
                        try{
                            (*it)->ReceiveData();
                            ++it;
                        }
                        catch (...){
                            (*it)->Close();
                            Close(it);
                        }
                    }
                }
            }
        }
        void Send(){
            for (auto o:cList){
                o->SendBuf();
            }
        }
        void CloseConn(){
            for (cListIt it=cList.begin();it!=cList.end();){
                if ((*it)->Closed()) Close(it); else ++it;
            }
        }
        inline void Manage(){
            Listen();
            Send();
            CloseConn();
        }
    };

} // MUD

#endif //MUD_CONNECTIONMANAGER_H
