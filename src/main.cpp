#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "menu.h"
#include "lan.h"

#define TFT_CS        2
#define TFT_DC        3 
#define TFT_RST       4

#define RADIO_CE       10
#define RADIO_CSP      9

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

void setup(void)
{
  Serial.begin(9600);

  initDisplay();
  // menu.render();
  displayChoiceChannel(0, 30);

  // lan.init();
  Serial.println("Scan network...");
}

byte n = 0;

void loop(void)
{

}
