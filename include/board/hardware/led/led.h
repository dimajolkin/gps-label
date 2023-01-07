#pragma once

#include <mbed.h>

class Led {
    private:
        DigitalOut *led;

    public:
        Led(PinName _pin) {
            led = new DigitalOut(_pin);
        }

        void on()
        {
            led->write(1);
        }

        void off()
        {
            led->write(0);
        }

        void toggle() 
        {
            led->write(led->read() ? 0 : 1);
        }

};