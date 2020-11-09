#pragma once

#include "lib/page/page.h"

#include "header/header.h"
#include "page/setting.h"
#include "page/map.h"

class App {
    private:
        Header *header;
        Page *current;
        Buttons *buttons;
        Display *display;
        Container *container;
        uint8_t stop = 0;
        uint16_t timing = 0;
    public:
    App(Display *display, Container *container): display(display), container(container) {
        header = new Header(display);
        buttons = new Buttons(BUTTON_PINS);

        current = new MapPage(display, header->getDy() + 1);
        // current = new ConnectionListPage(display, header->getDy() + 1);
    }

    void setup() {
        container->getLogger()->start();
        // container->getLogger()->attachDisplay(display);
        container->getLogger()->attachSerial();

        Serial.println(F("Start app"));

        display->initR(INITR_BLACKTAB); 
        display->setRotation(0);
        display->fillScreen(BACKGROUND_COLOR);

        display->println(F("Initilize lan.."));
        Lan *lan = container->getLan();
        lan->init();

        // режим согласования номеров 
        container->getMemberService()->start();

        buttons->setup();
        display->fillScreen(BACKGROUND_COLOR);

        start(header);
        start(current);

        Serial.println(F("run loop"));
    }

    void start(Renderer *view) {
        view->load();
        view->configure(container);
    }

    void registerHandlerKeyboard(ButtonConfig::EventHandler handleEvent) {
        buttons->setEventHandler(handleEvent);
    }

    void onClick(uint8_t btn) {
        Serial.println(F("Click"));
        current->onClick(btn);

        if (current->getNext() != NULL) {
            current = current->getNext();
            start(current);
        }
    }

    void tasks() {
        container->getServer()->update();
        container->getMemberService()->update();
    }

    void readPackages() {
        if (container->getLan()->available()) {
            Package pack = container->getLan()->read();
            if (pack.validate()) {
                container->getMemberService()->registerPakage(&pack);
            } else {
                 Serial.println(F("Failed..."));
            }
        }
    }

    void loop() {
        header->check();
        buttons->check();
        current->check();

        // update every 1s 
         if (millis() - timing > 1000) {
            timing = millis(); 
            tasks();
        }

        readPackages();
    }
};
