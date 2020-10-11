#pragma once


int serial_putc(char c, FILE *) {
    // tft.write(c);
    Serial.write(c);
    return c;
}

class Logger {
    private:
        Display *display;
    public:
        void start() {
            Serial.begin(SERIAL_BAUND);
            fdevopen(&serial_putc, 0);
        }

        void useDisplay(Display *display) {

        }

};