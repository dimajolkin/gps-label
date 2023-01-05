#pragma once

#include "app/service/member/member-service.h"
#include "framework/ui/render.h"
#include "board/board.h"
#include "board/hardware/logger/logger.h"
#include "app/task/task-manager.h"

class Container
{
private:
    Board *board;
    MemberService *memberService;
    Render *render;
    Logger *logger;
    TaskManager *taskManager;

public:
    Container(
        Board *board
    ) {
        this->board = board;
        this->logger = new Logger();
        this->memberService = new MemberService();
        this->taskManager = new TaskManager();
    }

    void setRender(Render *r)
    {
        render = r;
    }

    TaskManager *getTaskManager() 
    {
        return taskManager;
    }

    Board *getBoard()
    {
        return board;
    }

    Render *getRender()
    {
        return render;
    }

    Lan *getLanIn()
    {
        return board->getLanIn();
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