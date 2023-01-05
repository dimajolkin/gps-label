#pragma once

#include "config.h"
#include "framework/draw/point.h"
#include "board/hardware/display/display.h"

class MemoryElement {

    public:
        static void render(Point point, Display *display, uint16_t memory) {
            display->setTextCursor(point.x, point.y + 1);
            display->setTextSize(1);
            display->setTextWrap(true);
            display->fillRect(point.x, point.y + 1, 30, 10, BACKGROUND_COLOR);
            display->printf("%ib", memory);
        }
};