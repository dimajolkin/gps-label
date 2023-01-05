#pragma once

#include "app/service/member/member-service.h"
#include "framework/ui/render.h"
#include "board/board.h"
#include "board/hardware/logger/logger.h"

class ServiceLocator
{
private:
    Board *board;
    MemberService *memberService;
    Render *render;
    Logger *logger;

public:
    ServiceLocator(
        Board *board
    ) {
        this->board = board;
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
        return board->getLan();
    }

    Keyboard *getKeyboard()
    {
        return board->getKeyboard();
    }

    Display *getDisplay()
    {
        return board->getDisplay();
    }

    GPSDevice* getGPS() {
        return board->getGPS();
    }

    Storage *getStorage()
    {
        return board->getStorage();
    }

    Battery *getBattery()
    {
        return board->getBattery();
    }

    Server *getServer()
    {
        return board->getServer();
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