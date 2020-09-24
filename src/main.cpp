#include <Arduino.h>
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

int biggestMemoryBlock(uint16_t min,uint16_t max)
{
  if (min==max-1)
    return min;

  int size=max;
  int lastSize=size;
  byte *buf;
  while ((buf = (byte *) malloc(size)) == NULL)
  {
    lastSize=size;
    size-=(max-min)/2;
  };

  free(buf);
  return biggestMemoryBlock(size,lastSize);
};

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  Serial.println(biggestMemoryBlock(0, 4096));

  app.onClick(button->getId());
}



void setup(void)
{
  // lan.init();

  Serial.begin(9600);
  Serial.println("Start app");

  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void)
{
  app.loop();
}