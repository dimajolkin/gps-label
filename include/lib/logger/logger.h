#pragma once

#include "hardware/display/display.h"

Display *loggerDisplayLink = NULL;

class Logger {
    public:
        void start() {
            Serial.begin(SERIAL_BAUND);
        }

        void attachSerial() {
            fdev_close();
            fdevopen(&serialPutc, 0);
        }

        void attachDisplay(Display *disp) {
            loggerDisplayLink = disp;
            fdev_close();
            fdevopen(&displayPutc, 0);
        }

        void detachDisplay() {
            loggerDisplayLink = NULL;
            fdev_close();
        }

        static int serialPutc(char c, FILE *) {
            Serial.write(c);
            return c;
        }

        int inline static displayPutc(char c, FILE *) {
            Serial.write(c);
            loggerDisplayLink->write(c);
            return c;
        }
};
