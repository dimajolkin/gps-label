#pragma once

#include "PinDetect.h"
using namespace std::chrono;

class Button
{
private:
    // PinDetect *pin;
    DigitalIn *in;

public:
    Button(PinName _pin)
    {
        in = new DigitalIn(_pin);
        in->mode(PullUp);

        // pin = new PinDetect(_pin);
        // pin->mode(PullUp);
        // pin->setAssertValue(1);        
    }

    void onKeyPressed(Callback<void()> func) {
        // pin->setSampleFrequency(2ms);
        // pin->attach_asserted(func);
    }

    bool isPressed() {
        return !in->read();
    }
};