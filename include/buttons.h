#pragma once

#include <AceButton.h>
using namespace ace_button;

class Buttons {
  private:
    const uint8_t *pins;
    uint8_t count;
    AceButton buttons[BTN_PIN_COUNT];

  public:
    Buttons(const uint8_t *_pins) {
        pins = _pins;
        count = BTN_PIN_COUNT;
    }

    void setup() {
        for(uint8_t i = 0; i < count; i++) {
            pinMode(pins[i], INPUT_PULLUP);
            buttons[i].init(pins[i], HIGH, pins[i]);
        }
    }

    void setEventHandler(ButtonConfig::EventHandler handleEvent) {
        ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
        buttonConfig->setEventHandler(handleEvent);
        buttonConfig->setFeature(ButtonConfig::kFeatureClick);
        buttonConfig->setClickDelay(buttonConfig->getClickDelay() + 100);
    }

    void check() {
      for(uint8_t i = 0; i < count; i++) {
        buttons[i].check();
      }
    }
};