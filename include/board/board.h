#pragma once

#include "board/hardware/lan/lan.h"
#include "board/hardware/gps/gps.h"
#include "board/hardware/server/server.h"
#include "board/hardware/display/display.h"
#include "board/hardware/keyboard/keyboard.h"
#include "board/hardware/logger/logger.h"
#include "board/hardware/storage/storage.h"
#include "board/hardware/battery/battery.h"
#include "board/hardware/led/led.h"

class Board
{
private:
    Display *display;
    GPSDevice *gps;
    Keyboard *keyboard;
    Lan *lan;
    Storage *storage;
    Battery *battery;
    Server *server;
    Logger *logger;
    Led *led;

public:
    Board(
        Display *display,
        Keyboard *keyboard,
        Lan *lan,
        Storage *storage,
        Battery *battery,
        Server *server,
        GPSDevice *gps,
        Led *led
    ) {
        this->display = display;
        this->keyboard = keyboard;
        this->lan = lan;
        this->storage = storage;
        this->battery = battery;
        this->server = server;
        this->gps = gps;
        this->led = led;
    }

    Led *getLed()
    {
        return led;
    }

    Lan *getLanIn()
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

    GPSDevice *getGPS()
    {
        return gps;
    }

    Storage *getStorage()
    {
        return storage;
    }

    Battery *getBattery()
    {
        return battery;
    }

    Server *getServer()
    {
        return server;
    }
};