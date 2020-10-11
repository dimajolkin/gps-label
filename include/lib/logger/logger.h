#pragma once

// int serial_putc(char c, FILE *) {
//     Serial.write(c);
//     return c;
// }

// int display_puct(char c, FILE *) {
//     display.write(c);
//     return c;
// }

class Logger {
    private:
    public:
        static Display *display;
        void start() {
            Serial.begin(SERIAL_BAUND);
            attachSerial();
        }

        void attachSerial() {
            fdev_close();
            fdevopen(&serialPutc, 0);
        }

        void attachDisplay(Display *display) {
            display = display;
            fdev_close();
            fdevopen(&displayPutc, 0);
        }

        void detachDisplay() {
            display = NULL;
            fdev_close();
        }

        static int serialPutc(char c, FILE *) {
            Serial.write(c);
            return c;
        }

        static int displayPutc(char c, FILE *) {
            display->write(c);
            return c;
        }
};