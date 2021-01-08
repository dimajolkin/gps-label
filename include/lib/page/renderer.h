#pragma once

#include "config.h"
#include "hardware/display/display.h"
#include "container.h"

class Renderer {
    protected:
        static const uint16_t SLEEP_MS = 400;
        Display *display;
        uint8_t isRender = 0;
        uint8_t dy = 0;
        uint16_t timing = 0;
    public:
        Renderer(Display *display, uint8_t dy): display(display), dy(dy) {}
        Renderer(Display *display): display(display) {}
        virtual ~Renderer() {}

        void load() {
            clear();
            isRender = 0;
        }

        void clear() {
            display->fillRect(0, dy + 1, display->width(), display->height(), BACKGROUND_COLOR);
        }

        virtual void configure(Container *container) {}
        
        virtual void render();

        virtual void update() {};
        
        virtual void check() {
            if (!isRender) {
                render();
                isRender = 1;
            }

            if (millis() - timing > SLEEP_MS) {
               timing = millis(); 
               update();
            }
        }
};