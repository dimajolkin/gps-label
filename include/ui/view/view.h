#pragma once

#include "hardware/display/display.h"

class View
{
public:
    virtual void draw(Display *display) = 0;

    virtual void refresh() = 0;
};