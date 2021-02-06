// #include <Arduino.h>
// #include <EEPROM.h>

// #include "hardware/display/display.h"
// #include "hardware/server/server.h"
// #include "hardware/lan/lan.h"
// #include "hardware/gps/gps.h"

// #include "config.h"
// #include "buttons.h"
// #include "container.h"
// #include "app.h"
// #include "lib/logger/logger.h"
// #include "stdio.h"

// RF24 radio(RADIO_CE, RADIO_CSP);
// GPS gps(GPO_GPS_RX, GPO_GPS_TX);

// Display display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
// Logger *logger = new Logger();

// Lan lan(&radio);
// Container container(&gps, &lan, new Server(), logger);
// App app = App(&display, &container);

// void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

// void setup(void) {
//   SPIClass SPI_2(PB5, PB4, PB3);
//   SPI_2.begin();

//   app.setup();
//   app.registerHandlerKeyboard(handleEvent);
// }


// void loop(void) {
//     app.loop();
//     // printf(" hello, world! \n");
//     // ITM_SendChar('a');
// }

// void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
//   if (eventType != AceButton::kEventClicked) {
//     return;
//   } 
//   app.onClick(button->getId());
// }

#include "stdio.h"
#include "mbed.h"
#include "SWO.h"

#define WAIT_TIME_MS 200 
DigitalOut led1(LED1);

// SWO is on pin PB_3
// SWDIO is on pin PA_13
// SWCLK is on pin PA_14
SWO_Channel swo("channel");


int main() {
  swo.claim();            // capture <stdout>
  int count = 0;
  while(true) {
    printf("21Hello world2! %d\n", count);
    count++;
    led1 = !led1;
    wait_ms(WAIT_TIME_MS);
  }
}