#pragma once

#include "lib/ui/view.h"
#include "ui/model/menu.h"

class MenuView : public View
{
protected:
    uint8_t refFlag = 2;
private:
    MenuModel *model;
    const uint8_t dy = 0;

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
        display->printf("%s", item.name);
    }

public:
    MenuView(MenuModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->fillRect(0, dy + 1, 7, 5 * 10, ST7735_BLACK);
        display->setTextColor(ST7735_WHITE);
        display->setTextWrap(true);

        for (uint8_t i = 0; i < model->getElementsCount(); i++)
        {
            renderElement(display, model->getElement(i));
        }
    }
};