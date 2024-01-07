#pragma once

#include "board/hardware/display/display.h"
#include "lvgl.h"

void lvgl_display_flush() {

}

class LVGLDisplay
{
private:
    Display *disp;

public:
    LVGLDisplay(Display *disp): disp(disp) {

    }

    void init(
        void (*flush_cb)(struct _lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
    ) {
        disp->init();
        thread_sleep_for(100);
        lv_init();       
    
        static lv_disp_draw_buf_t disp_buf;

        /*Static or global buffer(s). The second buffer is optional*/
        static lv_color_t buf_1[240 * 10]; //TODO: Declare your own BUFF_SIZE appropriate to your system.
        static lv_color_t buf_2[240 * 10];

        lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 240 * 10);

        static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
        lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
        disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
        disp_drv.flush_cb = flush_cb;        /*Set a flush callback to draw to the display*/

        disp_drv.hor_res = disp->width();                 /*Set the horizontal resolution in pixels*/
        disp_drv.ver_res = disp->height();                 /*Set the vertical resolution in pixels*/

        lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
    }

    void flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
    {
        disp->flush(area->x1, area->y1, area->x2, area->y2, color_p);
        lv_disp_flush_ready(disp_drv);
    }
};
