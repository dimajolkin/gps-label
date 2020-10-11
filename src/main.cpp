#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
typedef Adafruit_ST7735 Display;

#include "config.h"
#include "buttons.h"
#include "devices/server/server.h"
#include "devices/lan/lan.h"
#include "container.h"
#include "app.h"
#include "lib/logger/logger.h"



RF24 radio(RADIO_CE ,RADIO_CSP);
Display display = Display(TFT_CS, TFT_DC, TFT_RST);
Logger *logger = new Logger();
Lan lan(&radio);
Container container(&lan, new Server(), logger);
App app = App(&display, &container);


void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

void setup(void)
{
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void)
{
    if (lan.available()) {
        // Package pack = lan.read();
        Serial.println(1);
    }

    app.loop();
}

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}
