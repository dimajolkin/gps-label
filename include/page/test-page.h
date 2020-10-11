#pragma once

#include "lib/page/page.h"

class TestPage: public Page {
    private:
        String str;
    public:
        TestPage(Display *display, uint8_t dy, String str): Page(display, dy), str(str) {}

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }
     
        void render() {
            display->setCursor(1, dy + 30);
            display->println(F("Test view"));
            display->println(str);
        }
};