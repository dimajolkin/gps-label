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
    Thread thread;

public:
    const static uint8_t SIZE = KEYBOARD_KEY_LEN;
    const static uint8_t KEY_UP = 0;
    const static uint8_t KEY_DOWN = 1;
    const static uint8_t KEY_LEFT = 2;
    const static uint8_t KEY_RIGHT = 3;
    const static uint8_t KEY_OK = 4;

    Keyboard(PinName _up, PinName _down, PinName _left, PinName _right, PinName _ok, Callback<void(uint8_t)> onKeyPressed)
    {
        keys[KEY_UP] = new Button(_up);
        keys[KEY_DOWN] = new Button(_down);
        keys[KEY_LEFT] = new Button(_left);
        keys[KEY_RIGHT] = new Button(_right);
        keys[KEY_OK] = new Button(_ok);
        _onKeyPressed = onKeyPressed;
    }

    void init()
    {
        for (uint8_t keyCode = 0; keyCode < SIZE; keyCode++)
        {
            keys[keyCode]->onKeyPressed([this, keyCode] {
                queue.call(_onKeyPressed, keyCode);
            });
        }

        thread.start(callback(&queue, &EventQueue::dispatch_forever));
    }
};