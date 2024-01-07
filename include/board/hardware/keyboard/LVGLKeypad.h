#pragma once

#include "board/hardware/keyboard/keyboard.h"
#include "lvgl.h"

class LVGLKeypad {
    Keyboard *keyboard;
    lv_indev_t *input;

    public:
        LVGLKeypad(Keyboard *keyboard): keyboard(keyboard) {}

        void init() {
            keyboard->init();

            lv_indev_drv_t indev_drv;                       //Descriptor of an input device driver
            lv_indev_drv_init(&indev_drv);                  //Basic initialization
            indev_drv.type = LV_INDEV_TYPE_KEYPAD;         //The touchpad is pointer type device
            // indev_drv.read_cb = keypad_read;              //Set the touchpad_read function
            input = lv_indev_drv_register(&indev_drv);              //Register touch driver in LvGL
        }

        void applyGroup(lv_group_t *g) {
            lv_indev_set_group(input, g); // group
        }
};