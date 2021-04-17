#include <Arduino.h>
#include <EEPROM.h>
// 
#include "hardware/display/display.h"
#include "hardware/server/server.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"

#include "config.h"
#include "buttons.h"
#include "container.h"
#include "app.h"
#include "lib/logger/logger.h"
#include "stdio.h"

RF24 radio(RADIO_CE, RADIO_CSP);
GPS gps(GPO_GPS_RX, GPO_GPS_TX);
Display display(TFT_CS, TFT_DC, TFT_RST);

Logger logger;
Server server;
Lan lan(&radio);

Container container(&gps, &lan, &server, &logger);
App app = App(&display, &container);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

void tick() {
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
}

void setup(void) {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PC13, OUTPUT); 

  //  SPIClass SPI_2(PB5, PB4, PB3);
  //  SPI_2.begin();
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void) {
  logger.printf("start \n");
    app.loop();
    // tick();
    logger.printf("stop \n");
}

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  }
  logger.printf("click! \n");
  app.onClick(button->getId());
}