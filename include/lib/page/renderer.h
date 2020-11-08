#pragma once

#include "config.h"
#include "hardware/display/display.h"
#include "container.h"

class Renderer {
    protected:
        Display *display;
        uint8_t is_render = 0;
        uint8_t dy = 0;
    public:
        Renderer(Display *display, uint8_t dy): display(display), dy(dy) {}
        Renderer(Display *display): display(display) {}
        virtual ~Renderer() {}

        void load() {
            clear();
            is_render = 0;
        }

        void clear() {
            display->fillRect(0, dy + 1, display->width(), display->height(), BACKGROUND_COLOR);
        }

        virtual void configure(Container *container) {}
        
        virtual void render();

        virtual void update() {};

        virtual void check() {
            if (!is_render) {
                render();
                is_render = 1;
            }
            update();
        }
};