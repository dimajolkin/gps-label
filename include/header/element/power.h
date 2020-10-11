#pragma once

#include "config.h"
#include "devices/display/display.h"

class PowerElement {
    private:
        static inline void renderBattery(Display *display, uint8_t dy, uint8_t x, uint8_t y, uint8_t percent) {
            const uint8_t w = 7;
            const uint8_t h = 8;
            uint8_t step = percent / (100 / (h + 1));
            uint16_t color = ST7735_WHITE;
            if (step < 2) {
                color = ST7735_RED;
            }
            for (uint8_t line = 1; line <= step; line++) {
                if (line == step) {
                    display->fillRect(x + 2, y + 1, 3, 1, color);
                } else {
                    display->fillRect(x, dy - 1 - line, w, 1, color);
                }
            }
        }
    public:
        static void render(Display *display, uint8_t dy, uint8_t power) {
            uint8_t x = 100;
            uint8_t y = 0;
            display->fillRect(x, y + 1, 24, 9, BACKGROUND_COLOR);
            display->setCursor(x, y + 1);
            display->setTextSize(1);
            display->print(power);
            display->write('%');
            renderBattery(display, dy, x + 20, y, 100);
        }
};