#pragma once

#include "lvgl.h"
#include "board/hardware/keyboard/LVGLKeypad.h"
#include "app/screen/BaseScreen.h"

class TestScreen : public BaseScreen
{
private:
    lv_obj_t *screen;
    LVGLKeypad *input;

public:
    TestScreen(lv_obj_t *screen, LVGLKeypad *input) : screen(screen), input(input)
    {
    }

    static void btn_event_cb(lv_event_t *e)
    {
        // lv_event_code_t code = lv_event_get_code(e);
        // lv_obj_t *btn = lv_event_get_target(e);
        // if (code == LV_EVENT_CLICKED)
        // {
        //     static uint8_t cnt = 0;
        //     cnt++;

        //     /*Get the first child of the button which is the label and change its text*/
        //     lv_obj_t *label = lv_obj_get_child(btn, 0);
        //     lv_label_set_text_fmt(label, "Button: %d", cnt);
        // }
    }

    // lv_obj_t *btn;

    // void lv_example_get_started_1(void)
    // {
    //     btn = lv_btn_create(lv_scr_act());                          /*Add a button the current screen*/
    //     lv_obj_set_pos(btn, 100, 10);                               /*Set its position*/
    //     lv_obj_set_size(btn, 120, 50);                              /*Set its size*/
    //     lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

    //     lv_obj_t *label = lv_label_create(btn); /*Add a label to the button*/
    //     lv_label_set_text(label, "Button");    /*Set the labels text*/
    //     lv_obj_center(label);
    // }

    void init()
    {
        // lv_group_t *g = lv_group_create();

        // auto ui_Screen1 = lv_scr_act();
        // lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE); /// Flags

        // lv_example_get_started_1();

        // auto ui_Switch1 = lv_switch_create(ui_Screen1);
        // lv_obj_set_width(ui_Switch1, 50);
        // lv_obj_set_height(ui_Switch1, 25);
        // lv_obj_set_x(ui_Switch1, -77);
        // lv_obj_set_y(ui_Switch1, -132);
        // lv_obj_set_align(ui_Switch1, LV_ALIGN_CENTER);

        // auto ui_Switch2 = lv_switch_create(ui_Screen1);
        // lv_obj_set_width(ui_Switch2, 50);
        // lv_obj_set_height(ui_Switch2, 25);
        // lv_obj_set_x(ui_Switch2, -75);
        // lv_obj_set_y(ui_Switch2, -96);
        // lv_obj_set_align(ui_Switch2, LV_ALIGN_CENTER);

        // auto ui_Switch3 = lv_switch_create(ui_Screen1);
        // lv_obj_set_width(ui_Switch3, 50);
        // lv_obj_set_height(ui_Switch3, 25);
        // lv_obj_set_x(ui_Switch3, -72);
        // lv_obj_set_y(ui_Switch3, -62);
        // lv_obj_set_align(ui_Switch3, LV_ALIGN_CENTER);

        // auto ui_Switch4 = lv_switch_create(ui_Screen1);
        // lv_obj_set_width(ui_Switch4, 50);
        // lv_obj_set_height(ui_Switch4, 25);
        // lv_obj_set_x(ui_Switch4, -72);
        // lv_obj_set_y(ui_Switch4, -27);
        // lv_obj_set_align(ui_Switch4, LV_ALIGN_CENTER);

        // lv_group_add_obj(g, ui_Switch1);
        // lv_group_add_obj(g, ui_Switch2);
        // lv_group_add_obj(g, ui_Switch3);
        // lv_group_add_obj(g, ui_Switch4);
        // lv_group_add_obj(g, btn);

        // // lv_indev_set_group(input, g); // group
        // input->applyGroup(g);
    }

    lv_key_t onKeypadRead(Keyboard::KEY key)
    {
        switch (key)
        {
        case Keyboard::KEY::UP:
            return LV_KEY_PREV;
        case Keyboard::KEY::DOWN:
            return LV_KEY_NEXT;
        case Keyboard::KEY::LEFT:
            return LV_KEY_LEFT;
        case Keyboard::KEY::RIGHT:
            return LV_KEY_RIGHT;
        case Keyboard::KEY::OK:
            return LV_KEY_ENTER;
        case Keyboard::KEY::NONE:
            return 0;
        };
        
        return 0;
    }
};
