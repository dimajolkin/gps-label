#pragma once

#include "lvgl.h"
#include "board/hardware/keyboard/keyboard.h"

class BaseScreen {
    public:
        virtual void init();

        virtual lv_key_t onKeypadRead(Keyboard::KEY key);
};