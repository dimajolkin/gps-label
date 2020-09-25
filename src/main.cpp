#include <Arduino.h>
#include "memory.h"

#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "config.h"
#include "buttons.h"
#include "devices/lan/lan.h"
#include "container.h"
#include "app.h"

RF24 radio(RADIO_CE ,RADIO_CSP); // CE, CSP
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
App app = App(&tft, new Container(new Lan(&radio)));

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Start app"));
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void)
{
  app.loop();
}