#pragma once

#include "config.h"

class MemoryElement {

    public:
        static void render(Display *display, uint16_t memory) {
            uint8_t x = 10;
            uint8_t y = 0;
            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->setTextWrap(true);
            display->fillRect(x, y + 1, 30, 10, BACKGROUND_COLOR);
            display->print(memory);
            display->print(F("b"));
        }
};