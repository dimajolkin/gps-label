#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#include "menu.h"
#include "lan.h"

#define TFT_CS        2
#define TFT_DC        3 
#define TFT_MOSI      4
#define TFT_SCLK      5
#define TFT_RST       6

#define RADIO_CE       10
#define RADIO_CSP      9

RF24 radio(RADIO_CE ,RADIO_CSP); // CE, CSP
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void initDisplay() {
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
}

Menu menu = Menu(&tft);
Lan lan = Lan(&radio);

void setup(void)
{
  Serial.begin(9600);

  initDisplay();
  menu.render();
  lan.init();
  Serial.println("Scan network...");
}
byte n = 0;
void loop(void)
{
  n++;
  if (n > 5) n = 0;
  menu.setActive(n);
  menu.render();

  lan.test();
}
