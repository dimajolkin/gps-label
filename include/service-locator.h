#pragma once

#include "app/service/member/member-service.h"
#include "framework/ui/render.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/server/server.h"
#include "hardware/display/display.h"
#include "hardware/keyboard/keyboard.h"
#include "hardware/logger/logger.h"
#include "hardware/storage/storage.h"

class ServiceLocator
{
private:
    Display *display;
    GPSDevice *gps;
    Keyboard *keyboard;
    Lan *lan;
    Storage *storage;
    Server *server;
    Logger *logger;
    MemberService *memberService;
    Render *render;

public:
    ServiceLocator(
        Display *display,
        Keyboard *keyboard,
        Lan *lan,
        Storage *storage,
        Server *server,
        GPSDevice *gps
    ) {
        this->display = display;
        this->keyboard = keyboard;
        this->lan = lan;
        this->storage = storage;
        this->server = server;
        this->gps = gps;
        this->logger = new Logger();
        this->memberService = new MemberService();
    }

    void setRender(Render *r)
    {
        render = r;
    }

    Render *getRender()
    {
        return render;
    }

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

    GPSDevice* getGPS() {
        return gps;
    }

    Storage *getStorage()
    {
        return storage;
    }

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