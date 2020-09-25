#include <Arduino.h>
#include "memory.h"

#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "config.h"
#include "buttons.h"
#include "devices/server/server.h"
#include "devices/lan/lan.h"
#include "container.h"
#include "app.h"

RF24 radio(RADIO_CE ,RADIO_CSP);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Lan lan(&radio);
Container container(&lan, new Server());
App app = App(&tft, &container);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Start app2"));
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void)
{
  app.loop();
}