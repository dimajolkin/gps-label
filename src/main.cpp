
// #define APP_DEBUG_BATTERY
#define APP
#include <mbed.h>
#include "config.h"
#include <stdint.h>
#include "board/hardware/display/display.h"
#include "board/hardware/lan/lan.h"
#include "board/hardware/gps/gps.h"
#include "board/hardware/storage/storage.h"
#include "board/hardware/keyboard/keyboard.h"
#include "board/hardware/battery/battery.h"
#include "board/hardware/led/led.h"
#include "board/board.h"
#include "app/container.h"
#include "runtime.h"




#ifdef APP
int main()
{
  // Led led(LED_PIN);
  // Storage storage(EEPROM_SDA, EEPROM_SCL);
  // storage.init();

  // while (true)
  // {
  //   led.toggle();
  //   thread_sleep_for(200);
  // }
 
  
  Storage storage(EEPROM_SDA, EEPROM_SCL);
  Board board(
      new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
      new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK),
      new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP, RADIO_IRQ, &storage),
      &storage,
      new Battery(BATTERY_MIN_VOLTAGE, BATTERY_MAX_VOLTAGE, BATTERY_REF_VOLTAGE, BATTERY_DIVIDER_RATION, BATTERY_PIN),
      new Server(),
      new GPSDevice(GPS_RX, GPS_TX),
      new Led(LED_PIN)
  );

  Container container(&board);

  AppRuntime runtime(&container);
  runtime.run();
}
#endif

#ifdef APP_DEBUG_BATTERY
int main()
{
  Thread batteryThread;
  batteryThread.start(taskBattry);

  while (true)
  {
    container->getLogger()->dispatch();
    led = !led;
    thread_sleep_for(200);
  }
}
#endif