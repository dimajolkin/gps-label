#pragma once

#include "mbed.h"
#include "button.h"

#define KEYBOARD_KEY_LEN 5

class Keyboard
{
private:
    Button *keys[KEYBOARD_KEY_LEN];
    Callback<void(uint8_t)> _onKeyPressed;
    EventQueue queue;
    
public:
    const static uint8_t SIZE = KEYBOARD_KEY_LEN;
    const static uint8_t KEY_UP = 0;
    const static uint8_t KEY_DOWN = 1;
    const static uint8_t KEY_LEFT = 2;
    const static uint8_t KEY_RIGHT = 3;
    const static uint8_t KEY_OK = 4;

    Keyboard(PinName _up, PinName _down, PinName _left, PinName _right, PinName _ok)
    {
        keys[KEY_UP] = new Button(_up);
        keys[KEY_DOWN] = new Button(_down);
        keys[KEY_LEFT] = new Button(_left);
        keys[KEY_RIGHT] = new Button(_right);
        keys[KEY_OK] = new Button(_ok);
    }

    void onKeyPressed(Callback<void(uint8_t)> func)
    {
        _onKeyPressed = func;
        for (uint8_t keyCode = 0; keyCode < SIZE; keyCode++)
        {
            keys[keyCode]->onKeyPressed([this, keyCode] {
                _onKeyPressed(keyCode);
            });    
        }
    }


    void init() {
        Thread keyboardThread;
        keyboardThread.start(callback(&queue, &EventQueue::dispatch_forever));
    }
};