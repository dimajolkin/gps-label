#pragma once

#include "hardware/display/display.h"
#include "app/model/lan-channel.h"
#include "framework/ui/view.h"

class LanChannelView : public View
{
private:
    Display *display;
    LanChannelModel *model;
    Lan *lan;

    static const uint16_t BACKGROUND_BLOCK = ST7735_BLUE;
    static const uint16_t BACKGROUND_ACTIVE_BLOCK = ST7735_GREEN;
    static const uint16_t BACKGROUND_SELECT_BLOCK = ST7735_YELLOW;
    static const uint16_t BACKGROUND_DISABLE = ST7735_BLACK;

    void selectBlock(uint8_t n)
    {
        if (lan->isChannelActive(n))
        {
            drawBlock(n, BACKGROUND_SELECT_BLOCK, BACKGROUND_BLOCK);
        }
        else
        {
            drawBlock(n, BACKGROUND_SELECT_BLOCK, BACKGROUND_DISABLE);
        }
    }

    void defaultBlock(uint8_t n)
    {
        drawBlock(n, BACKGROUND_BLOCK, BACKGROUND_BLOCK);
    }

    void disableBlock(uint8_t n)
    {
        drawBlock(n, BACKGROUND_DISABLE, BACKGROUND_DISABLE);
    }

    void block(uint8_t n)
    {
        if (n == model->getActive())
        {
            drawBlock(n, BACKGROUND_ACTIVE_BLOCK, BACKGROUND_BLOCK);
        }
        else if (lan->isChannelActive(n))
        {
            defaultBlock(n);
        }
        else
        {
            disableBlock(n);
        }
    }

    void drawBlock(uint8_t n, uint16_t color, uint16_t background)
    {
        uint8_t x = ((n - 1) % LanChannelModel::COUNT_BLOCKS_IN_LINE);
        uint8_t y = (n - 1) / LanChannelModel::COUNT_BLOCKS_IN_LINE;

        display->fillRoundRect((x * 20) + 3, (y * 20) + 5, 18, 18, 1, background);
        display->drawRect((x * 20) + 3, (y * 20) + 5, 18, 18, color);
        display->setTextCursor((x * 20) + 3, (y * 20) + 5 + 7);
        display->setTextColor(ST7735_WHITE);
        display->printf("%i", n);
    }

    // void setActive(uint8_t n)
    // {
    //     defaultBlock(active);
    //     active = n;
    //     block(active);
    //     lan->getConfig()->setChannel(active);
    // }

public:
    LanChannelView(LanChannelModel *model) : View(), model(model) {}

    void update(Display *_display)
    {
        display = _display;
        display->setTextCursor(0, 50);
        display->printf("Start scan chanels...");

        display->fillScreen(BACKGROUND_COLOR);
        for (uint8_t n = 1; n < lan->getCountChanels(); n++)
        {
            block(n);
        }
        // selectBlock(model->getSelected());
        // lan->stopTest();
    }
};