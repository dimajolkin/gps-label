#pragma once

#include <mbed.h>
#include "lib/ui/view.h"
#include "hardware/display/display.h"

class Render
{
private:
    View *view;
    EventFlags *refreshFlag;
    Thread *thread;
    Display *display;

    void refreshDraw()
    {
        refreshFlag->set(1);
    }

    void drawLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(1);
            refreshFlag->clear();
            if (view)
            {
                view->update(display);
            }
        }
    }
public:
    Render(Display *display) : display(display)
    {
        refreshFlag = new EventFlags();
        thread = new Thread();
    }

    void run()
    {
        thread->start(callback(this, &Render::drawLoop));
    }

    void setView(View *_view)
    {
        view = _view;
        refreshDraw();
    }
};