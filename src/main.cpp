#include <Arduino.h>
// #include <EEPROM.h>
// 
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

void setup(void) {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PC13, OUTPUT); 

//   SPIClass SPI_2(PB5, PB4, PB3);
//   SPI_2.begin();
      // display.initR(INITR_BLACKTAB); 
      // display.setRotation(0);
      // display.fillScreen(BACKGROUND_COLOR);
  // app.setup();
//   app.registerHandlerKeyboard(handleEvent);
}


void loop(void) {

  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);  

//     app.loop();
//  printf(" hello, world! \n");
//     // ITM_SendChar('a');
}

// void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
//   if (eventType != AceButton::kEventClicked) {
//     return;
//   } 
//   app.onClick(button->getId());
// }