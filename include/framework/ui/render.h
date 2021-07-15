#pragma once

#include <mbed.h>
#include "framework/ui/view.h"
#include "hardware/display/display.h"

class Render
{
private:
    long unsigned int FLAG_CONTENT = (1UL << 0);
    long unsigned int FLAG_LAYOUT = (1UL << 1);

    View *layoutView;
    View *contentView;
    EventFlags *refreshFlag;
    Thread *threadContent;
    Thread *threadLayout;
    Display *display;

    void refreshContent()
    {
        refreshFlag->set(FLAG_CONTENT);
    }

    void refreshLayout()
    {
        refreshFlag->set(FLAG_LAYOUT);
    }

    void drawViewContentLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(FLAG_CONTENT);
            printf("render content \n");
            contentView->update(display);
        }
    }

    void drawViewLayoutLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(FLAG_LAYOUT);
            printf("render layout \n");
            layoutView->update(display);
        }
    }

public:
    Render(Display *display, View *layoutView) : layoutView(layoutView), display(display)
    {
        refreshFlag = new EventFlags();
        threadContent = new Thread();
        threadLayout = new Thread();
    }

    void clear()
    {
        display->fillScreen(ST7735_BLACK);
        refreshLayout();
    }

    void run()
    {
        threadContent->start(callback(this, &Render::drawViewContentLoop));
        threadLayout->start(callback(this, &Render::drawViewLayoutLoop));
    }

    void setContentView(View *content)
    {
        contentView = content;
        refreshContent();
    }
};