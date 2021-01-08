#pragma once

#include "header/element/power.h"
#include "header/element/memory.h"
#include "lib/draw/point.h"

class Header: public Renderer {
    private:
        Server *server;
        MemberService *memberService;
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
            memberService = container->getMemberService();
        }

        uint8_t getDy() {
            return 11;
        }

        void renderPower() {
             PowerElement::render({100, 0}, display, power);
        }

        void renderMemory() {
            MemoryElement::render({10, 0}, display, memory);
        }

        void renderMember() {
            display->setCursor(display->width() / 2, 1);
            display->print(memberService->getMy()->getNumber());
        }

        void update() {
            tmp_power = server->getPowerPercent();
            tmp_memory = server->getAvailableMemory();

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
            renderMember();

            display->drawLine(
                0, getDy(),
                display->width(), getDy(),
                ST7735_WHITE
            );
        }
};