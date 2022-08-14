#pragma once

#include "framework/ui/view.h"
#include "app/view/header/element/memory.h"
#include "app/view/header/element/power.h"
#include "app/model/header.h"

class HeaderView : public View
{
private:
    HeaderModel *model;

    const uint8_t startX = 100;
    const uint8_t startY = 0;

    void renderPower(Display *display)
    {
        PowerElement::render({display->width() - 50, 0}, display, model->power);
    }

    void renderMemory(Display *display)
    {
        MemoryElement::render({10, 0}, display, model->memory);
    }

    void renderNumber(Display *display)
    {
        display->setTextCursor(display->width() / 2, 1);
        display->printf("%i", model->number);
    }

public:
    HeaderView(HeaderModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        
        // renderMemory(display);
        renderPower(display);
        renderNumber(display);

        display->drawLine(
            0, display->height(),
            display->width(), display->height(),
            ST7735_WHITE);
    }
};