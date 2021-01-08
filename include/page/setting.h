#pragma once

#include "lib/page/page.h"
#include "page/channel.h"
#include "page/test-page.h"
#include "page/member-list.h"

struct MenuElement {
    const uint8_t number;
    const char *name;
};

class Setting: public Page {
    private:
        uint8_t active = 1;
        const static uint8_t SIZE = 4;
        MenuElement elements[SIZE] = {
            {1, "LAN Channel"},
            {2, "Members"},
            {3, "GPS"},
            {4, "Logs"}
        };
        
        void renderElement(MenuElement item) {
            display->setCursor(1, dy + (item.number * 10));
            if (item.number == active) {
                display->print(F("* "));
            } else {
                display->print(F("  "));
            }
            display->print(item.number);
            display->print(F(". "));
            display->print(item.name);
        }

    public:
        Setting(Display *display, uint8_t dy): Page(display, dy) {}
        ~Setting() {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                return goBack();
            }

            if (btn == BTN_UP) {
                active--;
                isRender = 0;
            }

            if (btn == BTN_DOWN) {
                active++;
                isRender = 0;
            }

            if (btn == BTN_OK) {
                if (active == 1) {
                    return redirectTo(new ChannelPage(display, dy));
                } else if (active == 2) {
                    return redirectTo(new MemberListPage(display, dy));
                } else if (active == 3) {
                    return redirectTo(new TestPage(display, dy, "GPS"));
                } else if (active == 4) {
                    return redirectTo(new TestPage(display, dy, "Logs"));
                }
            }

            if (active > SIZE) active = SIZE;
            if (active < 1) active = 1;
        }

        void render() {
            display->fillRect(0, dy + 1, 7, 5 * 10, ST77XX_BLACK);
            display->setTextColor(ST77XX_WHITE);
            display->setTextWrap(true);

            for (uint8_t i = 0; i < SIZE; i++) {
                MenuElement item = elements[i];

                renderElement(item);
            }
        }
};
