#pragma once
#include "lib/logger/logger.h"

class Container {
    private:
        Lan *lan;
        Server *server;
        Logger *logger;
    public:
        Container(Lan *lan, Server *server, Logger *logger): lan(lan), server(server), logger(logger) {}
        
        Lan* getLan() {
            return lan;
        }

        Server* getServer() {
            return server;
        }

        Logger* getLogger() {
            return logger;
        }
};