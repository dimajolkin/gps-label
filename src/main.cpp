#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "config.h"
#include "buttons.h"
#include "menu.h"
#include "lan.h"

RF24 radio(RADIO_CE ,RADIO_CSP); // CE, CSP
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
}

Menu menu = Menu(&tft);
Lan lan = Lan(&radio);


void displayChoiceChannel(uint8_t x0, uint8_t y0) {
  const uint8_t dx = 2;

  tft.fillTriangle(0, y0 + 15, 30, y0, 30, y0 + 30, ST7735_RED);
  tft.drawRect(30 + dx, y0, 60, 30, ST7735_RED);
  tft.setCursor(30 + dx, y0 + 5);
  tft.setTextSize(3);
  tft.print(127);

  tft.fillTriangle(
    30 + 60 + dx + dx, y0,
    60 + 60 + dx + dx, y0 + 15,
    30 + 60 + dx + dx, y0 + 30,
    ST7735_RED
    );
}

const uint8_t BUTTON_PINS[BTN_PIN_COUNT] = {
   BTN_RIGHT,
   BTN_LEFT,
   BTN_UP,
   BTN_DOWN,
   BTN_OK,
};

Buttons buttons(BUTTON_PINS);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

void setup(void)
{
  Serial.begin(9600);

  initDisplay();
  // menu.render();

  // lan.init();
  Serial.println("Scan network...");

  buttons.init();
  buttons.setEventHandler(handleEvent);
}

byte n = 0;

void loop(void)
{
  buttons.check();
}

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 

  switch (button->getId())
  {
  case BTN_RIGHT:
    tft.println("right click");
    Serial.println("right click");
    break;
  case BTN_LEFT:
    tft.println("left click");
    Serial.println("left click");
    break;
  case BTN_UP:
    tft.println("up click");
    Serial.println("up click");
    break;
  case BTN_DOWN:
    tft.println("down click");
    Serial.println("down click");
    break;
  case BTN_OK:
    tft.println("ok click");
    Serial.println("ok click");
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    break;
  
  default:
    break;
  }
  
}