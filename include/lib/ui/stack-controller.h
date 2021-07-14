#pragma once

#include "lib/ui/controller.h"

class StackController
{
private:
    Controller *current;

public:
    StackController(Controller *current) : current(current) {}

    Controller *getCurrent()
    {
        return current;
    }

    void append(Controller* contr)
    {
        delete current;
        current = contr;
    }
};