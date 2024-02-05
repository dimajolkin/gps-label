#pragma once

#include "lvgl.h"
#include "board/hardware/keyboard/LVGLKeypad.h"
#include "app/screen/BaseScreen.h"

class LogScreen : public BaseScreen
{
private:
    lv_obj_t *screen;
    LVGLKeypad *input;

    lv_obj_t *textarea;

public:
    LogScreen(lv_obj_t *screen, LVGLKeypad *input) : screen(screen), input(input)
    {
    }

    void init()
    {
        // textarea = lv_textarea_create(screen);
        // lv_obj_set_size(textarea, LV_HOR_RES, 100);
        // lv_obj_set_pos(textarea, 0, 0);
    }

    void update(char c) 
    {
        // lv_textarea_add_char(textarea, c);
        
    }


    lv_key_t onKeypadRead(Keyboard::KEY key)
    {
        return LV_KEY_PREV;
    }
};