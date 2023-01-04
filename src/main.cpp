// #define APP_DEBUG_GPS
// #define APP_DEBUG_BATTERY
#define APP

#include <mbed.h>
#include "config.h"
#include <stdint.h>
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/storage/storage.h"
#include "hardware/keyboard/keyboard.h"
#include "hardware/battery/battery.h"
#include "service-locator.h"
#include "app/app.h"

DigitalOut led(PC_13);

void onKeyPressed(Keyboard::KEY key);

Storage storage(EEPROM_SDA, EEPROM_SCL);
Battery battary(BATTERY_MIN_VOLTAGE, BATTERY_MAX_VOLTAGE, BATTERY_REF_VOLTAGE, BATTERY_DIVIDER_RATION, BATTERY_PIN);


ServiceLocator *container = new ServiceLocator(
    new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
    new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK, onKeyPressed),
    new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP, &storage),
    &storage,
    new Server(),
    new GPSDevice(GPO_GPS_RX, GPO_GPS_TX)
);

App app(container);

void onKeyPressed(Keyboard::KEY key)
{
  if (key == Keyboard::KEY::OK)
  {
    container->getRender()->clear();
  }

  led = !led;
  app.onClick(key);
}

// void onMembersStart()
// {
//   Lan *lan = container->getLan();
//   MemberService *memberService = container->getMemberService();

//   while (true)
//   {
//     if (lan->available())
//     {
//       Package pack = lan->read();
//       if (pack.validate())
//       {
//         memberService->registerPakage(&pack);
//       }
//     }
//   }
// }

// RF24 *radio = container->getLan()->getRadio();
// 
// InterruptIn irq(PB_4);
// 
// uint32_t c = 0;

// https://github.com/nRF24/RF24/blob/master/examples/InterruptConfigure/InterruptConfigure.ino
// void interruptHandler()
// {

//   bool tx_ds, tx_df, rx_dr;
//   radio->whatHappened(tx_ds, tx_df, rx_dr);

//   container->getLogger()->printf("c %i \n", c++);
//   // container->getLogger()->printf("tdata_sent %i \n", tx_ds);
//   // container->getLogger()->printf("data_fail %i \n", tx_df);
//   // container->getLogger()->printf("data_ready %i \n", rx_dr);

//   // if (tx_df) {
//   //   radio->flush_tx();
//   // }
// }

void taskReadGps() {
  while (true) {
    container->getGPS()->read();
    thread_sleep_for(10);
  }
}

void taskBattry() {
  while (true) {
    container->getServer()->setPowerLevel(battary.level());
    thread_sleep_for(1000);
  }
}

#ifdef APP_DEBUG_GPS
void debugGPS()
{
  Thread reader;
  reader.start(taskReadGps);

  auto disp = container->getDisplay();
  disp->init();
  disp->setTextSize(2);
  disp->setTextColor(ST7735_WHITE);
  disp->printf("GPS init\n");

  container->getGPS()->init();
  disp->printf("GPS initialize\n");

  disp->printf("Wait read\n");

  while (true)
  {
    disp->setTextCursor(0, 50);
    disp->clearText(18);
    disp->setTextColor(ST7735_WHITE);

    auto dd = container->getGPS()->get();
    disp->printf("S:%i -- %.4f,%.4f", container->getGPS()->getCountSatellites(), (float) dd->lat, (float) dd->lng);

    led = !led;
    thread_sleep_for(1000); // 1s
  }
}
#endif

#ifdef APP
int main()
{
  app.init();
  
  Thread gpsThread;
  gpsThread.start(taskReadGps);

  Thread batteryThread;
  batteryThread.start(taskBattry);

  // Thread thread;
  // thread.start(onMembersStart);
  // irq.fall(&interruptHandler);

  while (true)
  {
    container->getLogger()->dispatch();
    led = !led;
    thread_sleep_for(100);
  }
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

#ifdef APP_DEBUG_GPS
int main()
{

  Thread debug;
  debug.start(debugGPS);
  // app.init();
  Thread thread;
  thread.start(onMembersStart);

  // // irq.fall(&interruptHandler);

  while (true)
  {
    container->getLogger()->dispatch();
    // led = !led;
    thread_sleep_for(100);
  }
}
#endif