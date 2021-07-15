#pragma once

#include "framework/ui/view.h"
#include "app/view/header/element/memory.h"
#include "app/view/header/element/power.h"

class HeaderView : public View
{
private:
    uint8_t power = 10;
    uint16_t memory = 1;
    uint8_t number = 0;

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


        // renderMemory(display);
        renderPower(display);
        // renderNumber(display);

        display->drawLine(
            0, display->height(),
            display->width(), display->height(),
            ST7735_WHITE);
    }
};