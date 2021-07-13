#pragma once

#include <mbed.h>
#include "SWO.h"
#include <stdio.h>
#include <stdarg.h>

class Logger
{
private:
    SWO_Channel *swo;
    EventQueue *queue;

public:
    Logger()
    {
        swo = new SWO_Channel("logger");
        queue = new EventQueue();
    }

    void printf(const char *format, ...)
    {
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
        swo->claim();
    }

    void dispatch()
    {
        queue->dispatch_once();
    }
};