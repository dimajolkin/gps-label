#pragma once

#include "lib/page/page.h"
#include "page/channel.h"
#include "page/test-page.h"

class Setting: public Page {
    private:
        uint8_t active = 1;

        void element(byte n, const char *chars) {
            display->setCursor(1, dy + (n * 10));
            if (n == active) {
                display->print(F("* "));
            } else {
                display->print(F("  "));
            }
            display->print(n);
            display->print(F(". "));
            display->print(chars);
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
                is_render = 0;
            }

            if (btn == BTN_DOWN) {
                active++;
                is_render = 0;
            }

            if (btn == BTN_OK) {
                if (active == 1) {
                    return redirectTo(new ChannelPage(display, dy));
                } else if (active == 2) {
                    return redirectTo(new TestPage(display, dy, "GPS"));
                } else if (active == 3) {
                    return redirectTo(new TestPage(display, dy, "Navigation"));
                } else if (active == 4) {
                    return redirectTo(new TestPage(display, dy, "Logs"));
                }
            }

            if (active > 4) active = 4;
            if (active < 1) active = 1;
        }

        void render() {
            display->fillRect(0, dy + 1, 7, 5 * 10, ST77XX_BLACK);
            display->setTextColor(ST77XX_WHITE);
            display->setTextWrap(true);

            element(1, "LAN Channel");
            element(2, "Connected");
            element(3, "Navigation");
            element(4, "Exit");
        }
};
