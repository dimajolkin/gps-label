#pragma once

#include "lib/page/page.h"
#include "device/member.h"
#include "device/members.h"

class MemberListPage: public Page {
    private:
        MemberService *service;
    public:
        MemberListPage(Display *display, uint8_t dy): Page(display, dy) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }

        void configure(Container *container) {
            service = container->getMemberService();
        }

        void renderAntenna(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t percent) {
            uint8_t len = round((w / 100.0) * percent);

            display->fillTriangle(
                x, y + h,
                x + len, y,
                x + len, y + h,
                ST77XX_WHITE
            );
        }

        void renderStats(uint8_t x, uint8_t y, Member *m) {
            display->setCursor(x + 10, y + 3);
            display->setTextSize(1);
            display->print("Count: ");
            display->print(m->getCountPakages());

            display->setCursor(x + 10, y + 13);
            display->print("Ping: ");
            display->print(m->getPing());
        }

        void renderMember(uint8_t n, Member *m) {
            uint8_t x = 0;
            uint8_t y = dy + (30 * n) + 2;

            display->fillRect(x, y, 128, 30, BACKGROUND_COLOR);
            if (m->isMy()) {
                display->drawRect(x, y, 128, 30, ST77XX_GREEN);
            } else {
                display->drawRect(x, y, 128, 30, ST77XX_WHITE);
            }
            
            display->setCursor(x + 5, y + 5);
            display->setTextSize(3);
            
            display->print(m->getNumber());
        
            renderStats(x + 15, y + 3, m);
            renderAntenna(x + 80, y + 3, 40, 25, 100);
        }
        
        void update() {
            uint8_t n = 0;
            for (size_t i = 0; i < service->getList()->getSize(); i++) {
                if (service->getList()->has(i)) {
                    renderMember(n, service->getList()->get(i));
                    n++;
                }
            }
        }
};