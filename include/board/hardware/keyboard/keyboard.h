#pragma once

#include "mbed.h"
#include "button.h"

#define KEYBOARD_KEY_LEN 5

class Keyboard
{
private:
    Button *keys[KEYBOARD_KEY_LEN];
    EventQueue queue;
    Thread thread;

public:
    enum KEY {UP, DOWN, LEFT, RIGHT, OK, NONE};
private:
    Callback<void(Keyboard::KEY)> _onKeyPressed;
public:
    const static uint8_t SIZE = KEYBOARD_KEY_LEN;

    Keyboard(PinName _up, PinName _down, PinName _left, PinName _right, PinName _ok)
    {
        keys[KEY::UP] = new Button(_up);
        keys[KEY::DOWN] = new Button(_down);
        keys[KEY::LEFT] = new Button(_left);
        keys[KEY::RIGHT] = new Button(_right);
        keys[KEY::OK] = new Button(_ok);
        
    }

    bool isPressed(Keyboard::KEY key)
    {
        return keys[key]->isPressed();
    }

    bool isPressed()
    {
        for (uint8_t keyCode = 0; keyCode < SIZE; keyCode++)
        {
            if (keys[keyCode]->isPressed()) {
                return true;
            }
        }
        return false;
    }

    Keyboard::KEY lastKey() {
        for (uint8_t keyCode = 0; keyCode < SIZE; keyCode++)
        {
            if (keys[keyCode]->isPressed()) {
                return KEY(keyCode);
            }
        }

        return KEY::NONE;
    }

    void onKeyPress(Callback<void(Keyboard::KEY)> onKeyPressed)
    {
        _onKeyPressed = onKeyPressed;
    }

    void init()
    {
        for (uint8_t keyCode = 0; keyCode < SIZE; keyCode++)
        {
            keys[keyCode]->onKeyPressed([this, keyCode] {
                if (_onKeyPressed) {
                    queue.call(_onKeyPressed, KEY(keyCode));
                }
            });
        }

        thread.start(callback(&queue, &EventQueue::dispatch_forever));
    }
};