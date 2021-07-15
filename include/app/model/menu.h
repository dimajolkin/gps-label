#pragma once

#include "framework/ui/model.h"

struct MenuElement
{
    const uint8_t number;
    const char *name;
};

class MenuModel : public Model
{
private:
    uint8_t active = 1;
    const static uint8_t SIZE = 4;
    MenuElement elements[SIZE] = {
        {1, "LAN Channel"},
        {2, "Members"},
        {3, "My number"},
        {4, "GPS"}};

public:
    uint8_t getActive()
    {
        return active;
    }

    uint8_t getElementsCount()
    {
        return SIZE;
    }

    MenuElement getElement(uint8_t index)
    {
        return elements[index];
    }

    bool isActive(MenuElement element)
    {
        return element.number == active;
    }

    void down()
    {
        active++;
        if (active > SIZE)
        {
            active = 1;
        }
    }

    void up()
    {
        active--;
        if (active < 1)
        {
            active = SIZE;
        }
    }
};