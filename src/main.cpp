#include <mbed.h>

#include "config.h"
#include <stdint.h>
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/keyboard/keyboard.h"
#include "service-locator.h"
#include "ui/app.h"

DigitalOut led(PC_13);

ServiceLocator *container = new ServiceLocator(
    new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
    new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK),
    new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP),
    new Server());
App app(container);

EventFlags displayDrawFlag;
uint8_t SAMPLE_FLAG1 = 1;

void onDisplayThread()
{
  while (true)
  {
    printf("draw \n");
    app.draw();
  }
}

// void onLanThread() {
//   lan.init();
//   // lan.test();
//   // thread_sleep_for(5000);
//   while(true) {
//     if (lan.available()) {
//       Package p = lan.read();
//       if (p.validate()) {
//         led = !led;
//         countPackages++;
//         displayDrawFlag.set(SAMPLE_FLAG1);
//       }
//     }

//     thread_sleep_for(100);
//   }
// }


void onClick(uint8_t key)
{
  // displayDrawFlag.set(SAMPLE_FLAG1);
  led = !led;
  app.onClick(key);
  // container->getLogger()->printf("hello %i \n", n);
}

Thread displayThread;
Thread lanThread;

int main()
{
  app.init();
  container->getKeyboard()->onKeyPressed(onClick);
  container->getLogger()->init();
  
  displayThread.start(onDisplayThread);

  // lanThread.start(onLanThread);
  printf("start app");
  while (1)
  {
    container->getLogger()->dispatch();
    thread_sleep_for(100);
  }
}