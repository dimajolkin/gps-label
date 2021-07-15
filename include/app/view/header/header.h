#pragma once

#include "framework/ui/view.h"
#include "app/view/header/element/memory.h"
#include "app/view/header/element/power.h"

class HeaderView : public View
{
private:
    uint8_t power = 0;
    uint8_t tmp_power = 0;

    uint16_t memory = 0;
    uint16_t tmp_memory = 0;

    uint8_t number = 0;
    uint8_t tmp_number = 0;

    const uint8_t startX = 100;
    const uint8_t startY = 0;

    void renderPower(Display *display)
    {
        PowerElement::render({100, 0}, display, power);
    }

    void renderMemory(Display *display)
    {
        MemoryElement::render({10, 0}, display, memory);
    }

    void renderNumber(Display *display)
    {
        display->setTextCursor(display->width() / 2, 1);
        display->printf("%i", number);
    }

public:
    void update(Display *display)
    {
        tmp_power = 10; 
        tmp_memory = 0;
        tmp_number = 1;
        // tmp_number = container->getGPS()->getCountSatellites();

        if (tmp_memory != memory)
        {
            memory = tmp_memory;
            renderMemory(display);
        }

        if (tmp_power != power)
        {
            power = tmp_power;
            renderPower(display);
        }

        if (tmp_number != number)
        {
            number = tmp_number;
            renderNumber(display);
        }

        display->drawLine(
            0, 11,
            display->width(), 11,
            ST7735_WHITE);
    }
};