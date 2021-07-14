#pragma once

#include "hardware/display/display.h"

class View
{
protected:
    uint8_t refFlag = 1;
    EventFlags *refreshFlag;
public:
    View() {
        static uint8_t id = 1;
        refFlag = id++;
        refreshFlag = new EventFlags();
    }

    virtual ~View() {
        refreshFlag->clear(refFlag);
        delete(refreshFlag);
    }

    virtual void update(Display *display) = 0;

    void draw(Display *display)
    {
        refreshFlag->wait_any(refFlag);
        refreshFlag->clear(refFlag);
        update(display);
    }

    void refresh()
    {
        refreshFlag->set(refFlag);
    }
};