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
    Window *contentWindow;
    Window *headerWindow;
    
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
            printf("render content \n");
            contentView->update(new Display(display, contentWindow));
        }
    }

    void drawViewHeaderLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(FLAG_HEADER);
            printf("render header \n");
            headerView->update(display);
        }
    }

public:
    Render(Display *display, View *headerView) : headerView(headerView), display(display)
    {
        refreshFlag = new EventFlags();
        threadContent = new Thread();
        threadLayout = new Thread();

        headerWindow = new Window(0, 0, display->width(), 11);
        contentWindow = new Window(0, 11, display->width(), display->height() - 11);
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