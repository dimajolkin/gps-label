#pragma once

#include "hardware/display/display.h"
#include <stdio.h>
// #include <SWOStream.h>
// #include <Print.h>

class Logger: public Print {
    private:
        SWOStream *swo;
    public:
        Logger() {
            swo = new SWOStream(6000, SWO_Async, 0, false);
        }

        size_t write(uint8_t ch) {
            return swo->write(ch);
        }

        size_t write(const uint8_t *buffer, size_t size) {
            return swo->write(buffer, size);
        }

        void flush() {
            swo->flush();
        }
};
