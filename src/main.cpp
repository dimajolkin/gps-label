#include <mbed.h>

#include "config.h"
#include <stdint.h>
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/keyboard/keyboard.h"
#include "service-locator.h"
#include "app/app.h"

DigitalOut led(PC_13);

void onKeyPressed(Keyboard::KEY key);

ServiceLocator *container = new ServiceLocator(
    new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
    new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK, onKeyPressed),
    new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP),
    new Server());

App app(container);



void onKeyPressed(Keyboard::KEY key)
{
  led = !led;
  app.onClick(key);
}

int main()
{
  container->getLan()->init();
  app.init();
  
  printf("start app \n");
  thread_sleep_for(100);
  while (true)
  {
    // container->getServer()->printMemoryInfo();
    thread_sleep_for(100);
  }
}
