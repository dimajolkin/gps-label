#pragma once

#include "header/element/power.h"
#include "header/element/memory.h"

class Header: public Renderer {
    private:
        Server *server;
        uint8_t power = 0;
        uint8_t tmp_power = 0;

        uint16_t memory = 0;
        uint16_t tmp_memory = 0;

        const uint8_t startX = 100;
        const uint8_t startY = 0;

        unsigned int timing;
    public:
        Header(Display *display): Renderer(display) {
        }

        void configure(Container *container) {
            server = container->getServer();
        }

        uint8_t getDy() {
            return 11;
        }

        void renderPower() {
             PowerElement::render(display, getDy(), power);
        }

        void renderMemory() {
            MemoryElement::render(display, memory);
        }

        void update() {
            if (millis() - timing > 1000) {
                timing = millis(); 
                tmp_power = server->getPowerPercent();
                tmp_memory = server->getAvailableMemory();
            }

            if (tmp_memory != memory) {
                memory = tmp_memory;
                renderMemory();
            }

            if (tmp_power != power) {
                power = tmp_power;
                renderPower();
            }
        }

        void render() {
            renderMemory();
            renderPower();

            display->drawLine(
                0, getDy(),
                display->width(), getDy(),
                ST7735_WHITE
            );
        }
};