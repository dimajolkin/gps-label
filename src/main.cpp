#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "config.h"
#include "buttons.h"
#include "lan.h"
#include "app.h"

// RF24 radio(RADIO_CE ,RADIO_CSP); // CE, CSP
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
}

// Menu menu = Menu(&tft);
// Lan lan = Lan(&radio);


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

App app = App(&tft);
void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}

void setup(void)
{
  initDisplay();

  // lan.init();
  displayChoiceChannel(20, 20);

  Serial.begin(9600);
  Serial.println("Start app");

  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}

void loop(void)
{
  app.loop();
}