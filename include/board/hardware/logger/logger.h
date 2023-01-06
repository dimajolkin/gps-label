#pragma once

#include <mbed.h>
#include "SWO.h"
#include <stdio.h>
#include <stdarg.h>


FileHandle *mbed::mbed_override_console(int fd)
{
    static SWO_Channel swo("errors");
    return &swo;
}

class Logger
{
private:
    SWO_Channel *swo;
    EventQueue *queue;
    bool isInit = false;

public:
    Logger()
    {
        swo = new SWO_Channel("logger");
        queue = new EventQueue();
    }

    void printf(const char *format, ...)
    {
        if (!isInit) {
            return;
        }

        char buffer[256];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        queue->call(::printf, buffer);
        va_end(args);
    }

    SWO_Channel* getSWO()
    {
        return swo;
    }

    void init()
    {
        isInit = true;
        swo->claim();
    }

    void dispatch()
    {
        queue->dispatch_once();
    }
};