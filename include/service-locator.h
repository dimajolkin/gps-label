#pragma once

#include "device/member-service.h"
#include "framework/ui/render.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/server/server.h"
#include "hardware/display/display.h"
#include "hardware/keyboard/keyboard.h"
#include "hardware/logger/logger.h"

class ServiceLocator
{
private:
    Display *display;
    // GPS *gps;
    Keyboard *keyboard;
    Lan *lan;
    Server *server;
    Logger *logger;
    MemberService *memberService;
    Render *render;

public:
    ServiceLocator(
        Display *display,
        Keyboard *keyboard,
        Lan *lan,
        Server *server)
    {
        this->display = display;
        this->keyboard = keyboard;
        this->lan = lan;
        this->server = server;
        this->logger = new Logger();
        this->memberService = new MemberService();
    }

    void setRender(Render *r)
    {
        render = r;
    }

    Render *getRender() { return render; }

    Lan *getLan()
    {
        return lan;
    }

    Keyboard *getKeyboard()
    {
        return keyboard;
    }

    Display *getDisplay()
    {
        return display;
    }

    // GPS* getGPS() {
    //     return gps;
    // }

    Server *getServer()
    {
        return server;
    }

    Logger *getLogger()
    {
        return logger;
    }

    MemberService *getMemberService()
    {
        return memberService;
    }
};