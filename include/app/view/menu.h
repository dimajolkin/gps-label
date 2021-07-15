#pragma once

#include "framework/ui/view.h"
#include "app/model/menu.h"

class MenuView : public View
{
private:
    MenuModel *model;
    const uint8_t dy = 20;

    void renderElement(Display *display, MenuElement item)
    {
        display->setTextCursor(1, dy + (item.number * 10));
        if (model->isActive(item))
        {
            display->printf("* ");
        }
        else
        {
            display->printf("  ");
        }
        display->printf("%i", item.number);
        display->printf(". ");
        display->printf("%s\n", item.name);
    }

public:
    MenuView(MenuModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->fillRect(0, dy + 1, 7, dy + (5 * 10), ST7735_BLACK);
        display->setTextSize(1);
        display->setTextColor(ST7735_WHITE);
        display->setTextWrap(true);

        for (uint8_t i = 0; i < model->getElementsCount(); i++)
        {
            renderElement(display, model->getElement(i));
        }
    }
};