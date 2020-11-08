#pragma once

#include "lib/logger/logger.h"
#include "device/members.h"

class Container {
    private:
        Lan *lan;
        Server *server;
        Logger *logger;
        MemberCollection *members;
    public:
        Container(Lan *lan, Server *server, Logger *logger): lan(lan), server(server), logger(logger) {
            members = new MemberCollection();
        }
        
        Lan* getLan() {
            return lan;
        }

        Server* getServer() {
            return server;
        }

        Logger* getLogger() {
            return logger;
        }

        MemberCollection* getMembers() {
            return members;
        }
};