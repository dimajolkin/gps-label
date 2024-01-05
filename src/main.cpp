
// #define APP_DEBUG_BATTERY
#include "mbed.h"
#include "lvgl.h"
#include "config.h"
#include <stdint.h>
#include "board/hardware/display/display.h"
#include "board/hardware/display/LVGLDisplay.h"
// #include "board/hardware/lan/lan.h"
// #include "board/hardware/gps/gps.h"
// #include "board/hardware/storage/storage.h"
#include "board/hardware/keyboard/keyboard.h"
// #include "board/hardware/battery/battery.h"
// #include "board/hardware/led/led.h"
// #include "board/board.h"
// #include "app/container.h"
// #include "runtime.h"

#define WIDTH 240
#define HEIGHT 320
#define BUFF_SIZE (240 * 10)
#define LVGL_TICK 5  //Time tick value for lvgl in ms (1-10msa)

FileHandle *mbed::mbed_override_console(int)
{
    static BufferedSerial custom_target_console(CONSOLE_TX, CONSOLE_RX);
    return &custom_target_console;
}

void lv_ticker_func();
void keypad_read(lv_indev_drv_t *indev, lv_indev_data_t *data);

LVGLDisplay display(new Display(APP_SPI_MOSI, APP_SPI_MISO, APP_SPI_SCK, TFT_CS, TFT_DC, TFT_RST));

Keyboard keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK);


static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

lv_obj_t * btn;

void onClick(Keyboard::KEY key)
{
  if (key == Keyboard::KEY::OK)
  {
      // lv_event_send(btn, LV_KEY_ENTER, NULL);
  }

  if (key == Keyboard::KEY::UP) {
      // lv_event_send(btn, LV_KEY_UP, NULL);
  }


  if (key == Keyboard::KEY::DOWN) {
      // lv_event_send(btn, LV_KEY_DOWN, NULL);
  }
}

void lv_example_get_started_1(void)
{
    btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 100, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}



void my_print(const char * buf)
{
    debug(buf);
}

void my_disp_flush_cb(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    display.flush(disp_drv, area, color_p);
}

int main()
{
  display.init(my_disp_flush_cb);
  lv_log_register_print_cb( my_print );

  keyboard.init();
  printf("Hello world!!");
  debug("Hello world");

  lv_group_t * g = lv_group_create();

  auto ui_Screen1 = lv_scr_act();
  lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

  lv_example_get_started_1();

  auto ui_Switch1 = lv_switch_create(ui_Screen1);
  lv_obj_set_width( ui_Switch1, 50);
  lv_obj_set_height( ui_Switch1, 25);
  lv_obj_set_x( ui_Switch1, -77 );
  lv_obj_set_y( ui_Switch1, -132 );
  lv_obj_set_align( ui_Switch1, LV_ALIGN_CENTER );


  auto ui_Switch2 = lv_switch_create(ui_Screen1);
  lv_obj_set_width( ui_Switch2, 50);
  lv_obj_set_height( ui_Switch2, 25);
  lv_obj_set_x( ui_Switch2, -75 );
  lv_obj_set_y( ui_Switch2, -96 );
  lv_obj_set_align( ui_Switch2, LV_ALIGN_CENTER );


  auto ui_Switch3 = lv_switch_create(ui_Screen1);
  lv_obj_set_width( ui_Switch3, 50);
  lv_obj_set_height( ui_Switch3, 25);
  lv_obj_set_x( ui_Switch3, -72 );
  lv_obj_set_y( ui_Switch3, -62 );
  lv_obj_set_align( ui_Switch3, LV_ALIGN_CENTER );


  auto ui_Switch4 = lv_switch_create(ui_Screen1);
  lv_obj_set_width( ui_Switch4, 50);
  lv_obj_set_height( ui_Switch4, 25);
  lv_obj_set_x( ui_Switch4, -72 );
  lv_obj_set_y( ui_Switch4, -27 );
  lv_obj_set_align( ui_Switch4, LV_ALIGN_CENTER );


  lv_group_add_obj(g, ui_Switch1);
  lv_group_add_obj(g, ui_Switch2);
  lv_group_add_obj(g, ui_Switch3);
  lv_group_add_obj(g, ui_Switch4);
  lv_group_add_obj(g, btn);


  lv_indev_drv_t indev_drv;                       //Descriptor of an input device driver
  lv_indev_drv_init(&indev_drv);                  //Basic initialization
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;         //The touchpad is pointer type device
  indev_drv.read_cb = keypad_read;              //Set the touchpad_read function
  auto input = lv_indev_drv_register(&indev_drv);              //Register touch driver in LvGL

  lv_indev_set_group(input, g);

  // ui_init();

  // run example
  // lv_example_get_started_1();

  //lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
  //lv_obj_set_size(spinner, 100, 100);
  //lv_obj_center(spinner);


    // lv_obj_t * spinner = lv_spinner_create(lv_screen_active());
    // lv_obj_set_size(spinner, 100, 100);
    // lv_obj_center(spinner);
    // lv_spinner_set_anim_params(spinner, 10000, 200);

  // Led led(LED_PIN);
  // Storage storage(EEPROM_SDA, EEPROM_SCL);
  // storage.init();

  // while (true)
  // {
  //   led.toggle();
  //   thread_sleep_for(200);
  // } 
  // Storage storage(EEPROM_SDA, EEPROM_SCL);
  // Board board(
  //     new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
  //     new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK),
  //     new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP, RADIO_IRQ, &storage),
  //     &storage,
  //     new Battery(BATTERY_MIN_VOLTAGE, BATTERY_MAX_VOLTAGE, BATTERY_REF_VOLTAGE, BATTERY_DIVIDER_RATION, BATTERY_PIN),
  //     new Server(),
  //     new GPSDevice(GPS_RX, GPS_TX),
  //     new Led(LED_PIN)
  // );

  // Container container(&board);

  // AppRuntime runtime(&container);
  // runtime.run();
  while(true) {
    lv_ticker_func();
    thread_sleep_for(5);
  }
}

void lv_ticker_func() {
    lv_tick_inc(LVGL_TICK); 
    //Call lv_tick_inc(x) every x milliseconds in a Timer or Task (x should be between 1 and 10). 
    //It is required for the internal timing of LittlevGL.
    lv_task_handler(); 
    //Call lv_task_handler() periodically every few milliseconds. 
    //It will redraw the screen if required, handle input devices etc.
}


void keypad_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    printf("KEYpress");
    if (keyboard.isPressed(Keyboard::KEY::UP)) {
      data->key = LV_KEY_PREV;
      data->state = LV_INDEV_STATE_PRESSED;
    } else if (keyboard.isPressed(Keyboard::KEY::DOWN)) {
      data->key = LV_KEY_NEXT;
      data->state = LV_INDEV_STATE_PRESSED;
    } else if (keyboard.isPressed(Keyboard::KEY::LEFT)) {
      data->key = LV_KEY_LEFT;
      data->state = LV_INDEV_STATE_PRESSED;
    } else if (keyboard.isPressed(Keyboard::KEY::RIGHT)) {
      data->key = LV_KEY_RIGHT;
      data->state = LV_INDEV_STATE_PRESSED;
    } else if (keyboard.isPressed(Keyboard::KEY::OK)) {
      data->key = LV_KEY_ENTER;
      data->state = LV_INDEV_STATE_PRESSED;
    } else {
      // data->key = NULL;
      data->state = LV_INDEV_STATE_RELEASED;
    }
}


// #ifdef APP_DEBUG_BATTERY
// int main()
// {
//   Thread batteryThread;
//   batteryThread.start(taskBattry);

//   while (true)
//   {
//     container->getLogger()->dispatch();
//     led = !led;
//     thread_sleep_for(200);
//   }
// }
// #endif