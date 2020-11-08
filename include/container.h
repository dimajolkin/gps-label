#pragma once

#include "lib/logger/logger.h"
#include "device/member-service.h"

class Container {
    private:
        Lan *lan;
        Server *server;
        Logger *logger;
       MemberService *memberService;
    public:
        Container(Lan *lan, Server *server, Logger *logger): lan(lan), server(server), logger(logger) {
            memberService = new MemberService();
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

        MemberService* getMemberService() {
            return memberService;
        }
};