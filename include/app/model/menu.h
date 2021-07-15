#pragma once

#include "framework/ui/model.h"

enum MenuElementEnum
{
    LAN_CHANNEL = 1,
    MEMBERS,
    TEST,
    GPS,
};

struct MenuElement
{
    const MenuElementEnum number;
    const char *name;
};

class MenuModel : public Model
{
private:
    uint8_t active = (uint8_t) MenuElementEnum::LAN_CHANNEL;
    const static uint8_t SIZE = 4;
    MenuElement elements[SIZE] = {
        {MenuElementEnum::LAN_CHANNEL, "LAN Channel"},
        {MenuElementEnum::MEMBERS, "Members"},
        {MenuElementEnum::TEST, "test"},
        {MenuElementEnum::GPS, "GPS"}};

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

    bool isActive(MenuElementEnum elementEnum)
    {
        return (uint8_t) elementEnum == active;
    }

    bool isActive(MenuElement element)
    {
        return (uint8_t) element.number == active;
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