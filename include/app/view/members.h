#pragma once

#include "hardware/display/display.h"
#include "app/model/members.h"
#include "framework/ui/view.h"

class MembersView : public View
{
private:
    MembersModel *model;

public:
    MembersView(MembersModel *model) : View(), model(model) {}

    void renderAntenna(Display *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t percent)
    {
        uint8_t len = round((w / 100.0) * percent);

        display->fillTriangle(
            x, y + h,
            x + len, y,
            x + len, y + h,
            ST7735_WHITE);
    }

    void renderStats(Display *display, uint8_t x, uint8_t y, Member *m)
    {
        display->setTextCursor(x + 10, y + 3);
        display->setTextSize(1);
        display->printf("Count: %i", m->getCountPakages());

        display->setTextCursor(x + 10, y + 13);
        display->printf("Ping: %i", m->getPing());
    }

    void renderMember(Display *display, uint8_t n, Member *m)
    {
        uint8_t x = 0;
        uint8_t y = (30 * n) + 2;

        display->setTextColor(ST7735_WHITE);
        display->fillRect(x, y, 128, 30, BACKGROUND_COLOR);
        if (m->isMy())
        {
            display->drawRect(x, y, 128, 30, ST7735_GREEN);
        }
        else
        {
            display->drawRect(x, y, 128, 30, ST7735_WHITE);
        }

        display->setTextCursor(x + 5, y + 5);
        display->setTextSize(3);

        display->printf("%i", m->getNumber());

        renderStats(display, x + 15, y + 3, m);
        renderAntenna(display, x + 80, y + 3, 40, 25, 100);
    }

    void update(Display *display)
    {
        uint8_t n = 0;
        for (size_t i = 0; i < model->members->getSize(); i++)
        {
            if (model->members->has(i))
            {
                renderMember(display, n, model->members->get(i));
                n++;
            }
        }
    }
};