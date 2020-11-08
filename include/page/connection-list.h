#pragma once

#include "lib/page/page.h"
#include "device/member.h"

class ConnectionListPage: public Page {
    public:
        ConnectionListPage(Display *display, uint8_t dy): Page(display, dy) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }

        void renderConnect(uint8_t n, Member m)
        {
            display->drawRect(0, 0, 20, 160, ST77XX_GREEN);
        }
     
        void render() {
            // renderConnect();
            display->setCursor(1, dy + 30);
            display->println(F("Connections list view"));
        }
};