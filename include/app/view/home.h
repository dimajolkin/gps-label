#pragma once

#include "hardware/display/display.h"
#include "app/model/home.h"
#include "framework/ui/view.h"

class HomeView : public View
{
private:
    HomeModel *model;

public:
    HomeView(HomeModel *model) : View(), model(model) {}

    void renderMenu(Display *display)
    {
        display->setTextColor(ST7735_WHITE);
        display->setTextCursor(display->width() - 25, display->height());
        display->setTextSize(1);
        display->printf("Menu");
    }

    void update(Display *display)
    {
        display->fillScreen(BACKGROUND_COLOR);
        uint8_t cx = display->width() / 2;
        uint8_t cy = 85;
        display->fillCircle(cx, cy, 2, ST7735_BLUE);
        for (uint8_t i = 0; i < HomeModel::MAX_RADIUS; i += model->radiusStep)
        {
            display->drawCircle(cx, cy, i, ST7735_GREEN);
        }

        renderMenu(display);
    }
};