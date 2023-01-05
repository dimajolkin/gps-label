#pragma once

#include "config.h"
#include "board/hardware/display/display.h"
#include "framework/draw/point.h"

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
        static void render(Point point, Display *display, uint8_t power) {
            display->fillRect(point.x, point.y + 1, 24, 9, BACKGROUND_COLOR);
            display->setTextColor(ST7735_WHITE);
            display->setTextCursor(point.x, point.y + 1);
            display->setTextSize(1);
            display->printf("%i%%", power);
            renderBattery(display, 11, point.x + 20, point.y, 100);
        }
};