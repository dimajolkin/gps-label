// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: GpsLabel

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Switch1 = lv_switch_create(ui_Screen1);
lv_obj_set_width( ui_Switch1, 50);
lv_obj_set_height( ui_Switch1, 25);
lv_obj_set_x( ui_Switch1, -10 );
lv_obj_set_y( ui_Switch1, -97 );
lv_obj_set_align( ui_Switch1, LV_ALIGN_CENTER );


ui_Switch2 = lv_switch_create(ui_Screen1);
lv_obj_set_width( ui_Switch2, 50);
lv_obj_set_height( ui_Switch2, 25);
lv_obj_set_x( ui_Switch2, -8 );
lv_obj_set_y( ui_Switch2, -58 );
lv_obj_set_align( ui_Switch2, LV_ALIGN_CENTER );


ui_Switch3 = lv_switch_create(ui_Screen1);
lv_obj_set_width( ui_Switch3, 50);
lv_obj_set_height( ui_Switch3, 25);
lv_obj_set_x( ui_Switch3, -7 );
lv_obj_set_y( ui_Switch3, -17 );
lv_obj_set_align( ui_Switch3, LV_ALIGN_CENTER );


ui_Switch4 = lv_switch_create(ui_Screen1);
lv_obj_set_width( ui_Switch4, 50);
lv_obj_set_height( ui_Switch4, 25);
lv_obj_set_x( ui_Switch4, -4 );
lv_obj_set_y( ui_Switch4, 24 );
lv_obj_set_align( ui_Switch4, LV_ALIGN_CENTER );



}
