#pragma once

#include "board/hardware/display/display.h"

class View
{
protected:
    uint8_t refFlag = 1;
public:
    View() {
        static uint8_t id = 1;
        refFlag = id++;
    }

    virtual ~View() {}

    uint8_t getId() {
        return refFlag;
    }

    virtual void update(Display *display) = 0;
};