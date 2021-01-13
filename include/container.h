#pragma once

#include "lib/logger/logger.h"
#include "device/member-service.h"
#include "hardware/gps/gps.h"

class Container {
    private:
        GPS *gps;
        Lan *lan;
        Server *server;
        Logger *logger;
        MemberService *memberService;
        
    public:
        Container(GPS *gps, Lan *lan, Server *server, Logger *logger): gps(gps), lan(lan), server(server), logger(logger) {
            memberService = new MemberService();
        }
        
        Lan* getLan() {
            return lan;
        }

        GPS* getGPS() {
            return gps;
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