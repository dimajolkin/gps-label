#pragma once

#include <mbed.h>
#include "framework/ui/view.h"
#include "framework/ui/view-render.h"
#include "hardware/display/display.h"

class Render
{
private:
    long unsigned int FLAG_CONTENT = (1UL << 0);
    long unsigned int FLAG_HEADER = (1UL << 1);
    Mutex *mutex;
    EventFlags *refreshFlag;
    Display *display;
    ViewRender *header;
    ViewRender *content;
    View *headerView;

public:
    Render(Display *display, View *headerView) : display(display), headerView(headerView) {}

    void clear()
    {
        mutex->lock();
        display->fillScreen(BACKGROUND_COLOR);
        mutex->unlock();
        header->refresh();
    }

    void init()
    {
        mutex = new Mutex();
        refreshFlag = new EventFlags();

        header = new ViewRender(
            new Display(display, new Window(0, 0, display->width(), 11)),
            headerView,
            mutex,
            refreshFlag,
            FLAG_HEADER,
            1000 * 2 // 2s
        );

        content = new ViewRender(
            new Display(display, new Window(0, 12, display->width(), display->height() - 12)),
            NULL,
            mutex,
            refreshFlag,
            FLAG_CONTENT);

        header->start();
        content->start();
    }

    void setContentView(View *viewContent)
    {
        content->setView(viewContent);
    }
};