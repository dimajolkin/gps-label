#define LV_USE_LOG 0

// #define APP_DEBUG_BATTERY
#include "mbed.h"
#include "lvgl.h"
#include "config.h"
#include <stdint.h>
#include "board/hardware/display/display.h"
#include "board/hardware/display/LVGLDisplay.h"
#include "board/hardware/lan/lan.h"
#include "board/hardware/gps/gps.h"
#include "board/hardware/storage/storage.h"
#include "board/hardware/keyboard/keyboard.h"
#include "board/hardware/keyboard/LVGLKeypad.h"
#include "board/hardware/battery/battery.h"
#include "board/hardware/led/led.h"
// #include "board/board.h"
// #include "app/container.h"
// #include "runtime.h"
#include "app/screen/BaseScreen.h"
#include "app/screen/TestScreen.h"
#include "app/screen/LogScreen.h"


#define WIDTH 240
#define HEIGHT 320
#define BUFF_SIZE (240 * 10)
#define LVGL_TICK 5  //Time tick value for lvgl in ms (1-10msa)

FileHandle *mbed::mbed_override_console(int)
{
    static BufferedSerial custom_target_console(CONSOLE_TX, CONSOLE_RX);
    return &custom_target_console;
}

void lvTickerFunc();
void onKeypadRead(lv_indev_t * indev, lv_indev_data_t * data);

LVGLDisplay display(new Display(APP_SPI_MOSI, APP_SPI_MISO, APP_SPI_SCK, TFT_CS, TFT_DC, TFT_RST));

Keyboard keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK);
LVGLKeypad keypad(&keyboard);
GPSDevice gps = GPSDevice(GPS_RX, GPS_TX);
Storage storage = Storage(EEPROM_SDA, EEPROM_SCL);
Battery battery = Battery(BATTERY_MIN_VOLTAGE, BATTERY_MAX_VOLTAGE, BATTERY_REF_VOLTAGE, BATTERY_DIVIDER_RATION, BATTERY_PIN);
Lan lan = Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP, RADIO_IRQ, &storage);
Led led = Led(LED_PIN);


TestScreen *screen;

#if LV_USE_LOG
void my_print(const char * buf)
{
    debug(buf);
}
#endif

void my_disp_flush_cb(lv_display_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    display.flush(disp_drv, area, color_p);
}

int main()
{
  display.init(my_disp_flush_cb);
  thread_sleep_for(100);
  #if LV_USE_LOG
  lv_log_register_print_cb( my_print );
  #endif

  // keypad.init(onKeypadRead);
  gps.init();
  storage.init();


  printf("Hello world!!");
  debug("Hello world");

  screen = new TestScreen(
    lv_scr_act(),
    &keypad
  );

  // screen = new LogScreen(lv_scr_act(), &keypad);

  screen->init();


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

  auto serial = gps.getSerial();

  char read_buffer[1] = {0};
  while(true) {
    lvTickerFunc();
    thread_sleep_for(1);

    // if (serial->read(&read_buffer, sizeof(char))) {
      // debug(&read_buffer[0]);
      // screen->update(read_buffer[0]);
    // }
  }
}

void lvTickerFunc() {
    lv_tick_inc(LVGL_TICK); 
    //Call lv_tick_inc(x) every x milliseconds in a Timer or Task (x should be between 1 and 10). 
    //It is required for the internal timing of LittlevGL.
    lv_task_handler(); 
    //Call lv_task_handler() periodically every few milliseconds. 
    //It will redraw the screen if required, handle input devices etc.
}


void onKeypadRead(lv_indev_t *indev, lv_indev_data_t *data)
{
  // if (keyboard.isPressed()) {
  //   auto lastKey = keyboard.lastKey();
  //   data->key = screen->onKeypadRead(lastKey);
  //   data->state = LV_INDEV_STATE_PRESSED;
  // } else {
  //   data->state = LV_INDEV_STATE_RELEASED;
  // }
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