//
// Created by root on 5/13/22.
//

#ifndef MUD_CONNECTIONHANDLER_H
#define MUD_CONNECTIONHANDLER_H

#include "Connection.h"
namespace MUD {
    template<typename protocol,typename commandType>
    class ConnectionHandler {
    protected:
        Connection<protocol> *connection;
    public:
        ConnectionHandler(Connection<protocol>& conn):connection(&conn){};
        virtual ~ConnectionHandler(){delete connection;};
        virtual void Handle(commandType command)=0;
        virtual void Enter()=0;
        virtual void Leave()=0;
    };

}

#endif //MUD_CONNECTIONHANDLER_H
