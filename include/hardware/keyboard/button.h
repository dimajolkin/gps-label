#include "PinDetect.h"

class Button
{
private:
    PinDetect *pin;

public:
    Button(PinName _pin)
    {
        pin = new PinDetect(_pin);
        pin->mode(PullUp);
        pin->setAssertValue(1);        
    }

    void onKeyPressed(Callback<void()> func) {
        pin->setSampleFrequency();
        pin->attach_asserted(func);
    }
};