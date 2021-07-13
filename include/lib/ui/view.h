#pragma once

#include "hardware/display/display.h"

class View
{
protected:
    uint8_t refFlag = 1;
    EventFlags *refreshFlag;
public:
    View() {
        refreshFlag = new EventFlags();
    }

    virtual ~View() {
        delete(refreshFlag);
    }

    virtual void update(Display *display) = 0;

    void draw(Display *display)
    {
        refreshFlag->wait_any(refFlag);
        refreshFlag->clear();
        update(display);
    }

    void refresh()
    {
        refreshFlag->set(refFlag);
    }
};