#pragma once

#include <mbed.h>
#include "framework/ui/view.h"
#include "hardware/display/display.h"

class ViewRender
{
private:
    Display *display;
    View *view;
    Mutex *mutex;
    Thread *thread;
    EventFlags *refreshFlag;
    long unsigned int eventFlag;
    uint32_t waitMillisec;

    void drawViewLoop()
    {
        while (true)
        {
            refreshFlag->wait_any(eventFlag, waitMillisec);
            if (view)
            {
                mutex->lock();
                view->update(display);
                mutex->unlock();
            }
        }
    }

public:
    ViewRender(
        Display *display,
        View *view,
        Mutex *mutex,
        EventFlags *refreshFlag,
        long unsigned int eventFlag,
        uint32_t waitMillisec = osWaitForever) : display(display),
                                                 view(view),
                                                 mutex(mutex),
                                                 refreshFlag(refreshFlag),
                                                 eventFlag(eventFlag),
                                                 waitMillisec(waitMillisec)
    {}

    void setView(View *_view)
    {
        view = _view;
        refresh();
    }

    void start()
    {
        thread = new Thread();
        thread->start(callback(this, &ViewRender::drawViewLoop));
    }

    void refresh()
    {
        refreshFlag->set(eventFlag);
    }
};