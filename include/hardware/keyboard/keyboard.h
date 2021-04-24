#include "mbed.h"

#include "button.h"

class Keyboard
{
private:
    Button *up;
    Button *down;
    Button *left;
    Button *right;
    Button *ok;
    Callback<void(uint8_t)> _onKeyPressed;

public:
    const static uint8_t KEY_UP = 0;
    const static uint8_t KEY_DOWN = 1;
    const static uint8_t KEY_LEFT = 2;
    const static uint8_t KEY_RIGHT = 3;
    const static uint8_t KEY_OK = 4;

    Keyboard(PinName _up, PinName _down, PinName _left, PinName _right, PinName _ok)
    {
        up = new Button(_up);
        down = new Button(_down);
        left = new Button(_left);
        right = new Button(_right);
        ok = new Button(_ok);
    }

    void onKeyPressed(Callback<void(uint8_t)> func)
    {
        _onKeyPressed = func;
        
        up->onKeyPressed([this] {
            _onKeyPressed(KEY_UP);
        });
        down->onKeyPressed([this] {
            _onKeyPressed(KEY_DOWN);
        });
        left->onKeyPressed([this] {
            _onKeyPressed(KEY_LEFT);
        });
        right->onKeyPressed([this] {
            _onKeyPressed(KEY_RIGHT);
        });
        ok->onKeyPressed([this] {
            _onKeyPressed(KEY_OK);
        });
    }
};