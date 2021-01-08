#pragma once

#include "config.h"
#include "lib/draw/point.h"

class MemoryElement {

    public:
        static void render(Point point, Display *display, uint16_t memory) {
            display->setCursor(point.x, point.y + 1);
            display->setTextSize(1);
            display->setTextWrap(true);
            display->fillRect(point.x, point.y + 1, 30, 10, BACKGROUND_COLOR);
            display->print(memory);
            display->print(F("b"));
        }
};