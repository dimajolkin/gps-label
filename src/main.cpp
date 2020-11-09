#include <Arduino.h>
#include <EEPROM.h>

#include "hardware/display/display.h"
#include "hardware/server/server.h"
#include "hardware/lan/lan.h"

#include "config.h"
#include "buttons.h"
#include "container.h"
#include "app.h"
#include "lib/logger/logger.h"

RF24 radio(RADIO_CE, RADIO_CSP);
Display display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Logger *logger = new Logger();

Lan lan(&radio);
Container container(&lan, new Server(), logger);
App app = App(&display, &container);

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

void buttonTick() {
  // app.event();
}

void setup(void)
{
  // подключили кнопку на D2 и GND
  // pinMode(6, INPUT_PULLUP);
  // D2 это прерывание 0
  // обработчик - функция buttonTick
  // FALLING - при нажатии на кнопку будет сигнал 0, его и ловим
  // attachInterrupt(0, buttonTick, FALLING);

  app.setup();
  app.registerHandlerKeyboard(handleEvent);
}


void loop(void)
{
    app.loop();
}

void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
  if (eventType != AceButton::kEventClicked) {
    return;
  } 
  app.onClick(button->getId());
}
