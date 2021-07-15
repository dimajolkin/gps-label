#pragma once

#include <mbed.h>
#include "framework/ui/view.h"
#include "hardware/display/display.h"

class Render
{
private:
    long unsigned int FLAG_CONTENT = (1UL << 0);
    long unsigned int FLAG_HEADER = (1UL << 1);

    View *headerView;
    View *contentView;
    EventFlags *refreshFlag;
    Thread *threadContent;
    Thread *threadLayout;
    Display *display;
    Display *headerDisplay;
    Display *contentDisplay;
    
    void refreshContent()
    {
        refreshFlag->set(FLAG_CONTENT);
    }

    void refreshHeader()
    {
        refreshFlag->set(FLAG_HEADER);
    }

    void drawViewContentLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(FLAG_CONTENT);
            contentView->update(contentDisplay);
        }
    }

    void drawViewHeaderLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(FLAG_HEADER, 1000 * 2); // 2s
            // printf("render header \n");
            headerView->update(headerDisplay);
        }
    }

public:
    Render(Display *display, View *headerView) : headerView(headerView), display(display)
    {
        refreshFlag = new EventFlags();
        threadContent = new Thread();
        threadLayout = new Thread();

        headerDisplay = new Display(display, new Window(0, 0, display->width(), 11));
        contentDisplay = new Display(display, new Window(0, 12, display->width(), display->height() - 12));
    }

    void clear()
    {
        display->fillScreen(ST7735_BLACK);
        refreshHeader();
    }

    void run()
    {
        threadContent->start(callback(this, &Render::drawViewContentLoop));
        threadLayout->start(callback(this, &Render::drawViewHeaderLoop));
    }

    void setContentView(View *content)
    {
        contentView = content;
        refreshContent();
    }
};