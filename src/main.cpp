#include <Arduino.h>
#include <EEPROM.h>

#include "hardware/display/display.h"
#include "hardware/server/server.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"

#include "config.h"
#include "buttons.h"
#include "container.h"
#include "app.h"
#include "lib/logger/logger.h"
RF24 radio(RADIO_CE, RADIO_CSP);
GPS gps(GPO_GPS_RX, GPO_GPS_TX);

Display display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Logger *logger = new Logger();

Lan lan(&radio);
Container container(&gps, &lan, new Server(), logger);
App app = App(&display, &container);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

void setup(void) {
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}


void loop(void) {
    app.loop();
}

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}
