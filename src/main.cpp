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

int serial_putc(char c, FILE *) {
    // tft.write(c);
    Serial.write(c);
    return c;
}

void printfBegin(void) {
   fdevopen(&serial_putc, 0 );
}

Lan lan(&radio);
Container container(&lan, new Server());
App app = App(&tft, &container);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}

const byte address[6] = "00001";
void setup(void)
{
  printfBegin();
  Serial.begin(9600);
  Serial.println(F("Start app"));
  app.setup();
  app.registerHandlerKeyboard(handleEvent);
  //radio.openReadingPipe(1, address);
}

void loop(void)
{
    // if (lan.available()) {
    //   Package *pack = lan.read();
    //   Serial.println("-- YES --- ");
    //   Serial.println(pack->getLan());
    //   Serial.println(pack->getLng());
    //   Serial.println(pack->getNumber());
    // }
  app.loop();
}