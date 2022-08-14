#define APP_DEBUG_GPS 
// #define APP 


#include <mbed.h>
#include "config.h"
#include <stdint.h>
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/storage/storage.h"
#include "hardware/keyboard/keyboard.h"
#include "service-locator.h"
#include "app/app.h"

DigitalOut led(PC_13);

void onKeyPressed(Keyboard::KEY key);

Storage storage(EEPROM_SDA, EEPROM_SCL);

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
  led = !led;
  app.onClick(key);
}

void onMembersStart()
{
  Lan *lan = container->getLan();
  MemberService *memberService = container->getMemberService();

  while (true)
  {
    if (lan->available())
    {
      Package pack = lan->read();
      if (pack.validate())
      {
        memberService->registerPakage(&pack);
      }
    }
  }
}


RF24 *radio = container->getLan()->getRadio();

InterruptIn irq(PB_4);

uint32_t c = 0;

// https://github.com/nRF24/RF24/blob/master/examples/InterruptConfigure/InterruptConfigure.ino
void interruptHandler() {
  
  bool tx_ds, tx_df, rx_dr;
  radio->whatHappened(tx_ds, tx_df, rx_dr); 

  container->getLogger()->printf("c %i \n", c++);
  // container->getLogger()->printf("tdata_sent %i \n", tx_ds);
  // container->getLogger()->printf("data_fail %i \n", tx_df);
  // container->getLogger()->printf("data_ready %i \n", rx_dr);

  // if (tx_df) {
  //   radio->flush_tx();
  // }
}



void debugGPS() {
  auto disp = container->getDisplay();
  disp->init();
  disp->setTextSize(1);
  disp->setTextColor(ST7735_WHITE);
  disp->printf("init GPS1\n");

  container->getGPS()->init();

  disp->printf("Wait read\n");
  disp->setTextWrap(false);
  printf("Tick\n");

  uint8_t s = 0;
  while(true) {
    container->getGPS()->update();
    // UnbufferedSerial *ss = container->getGPS()->getSerial();

    // char c[1];
    // ss->read(c, sizeof(char));
    // container->getDisplay()->writeChar(c[0]);
    // if (c[0] == '\n') {
    //   s++;
    // }
    
    auto dd = container->getGPS()->get();
    if (dd->lat) {
      disp->printf("LAT: %f, LNG %f \n", dd->lat, dd->lng);
      led = !led;
    }
    
    // printf("LAT: %f, LNG %f \n", dd->lat, dd->lng);
    // thread_sleep_for(100);
  }

  container->getDisplay()->setTextColor(ST7735_GREEN);
  container->getDisplay()->printf("SUCCESS\n");
}


#ifdef APP
  int main()
  {
    Thread debug;
    app.init();
    Thread thread;
    thread.start(onMembersStart);
    // irq.fall(&interruptHandler);

    while (true)
    {
      container->getLogger()->dispatch();
      led = !led;
      thread_sleep_for(100);
    }
}
#endif

#ifdef DEBUG_GPS
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