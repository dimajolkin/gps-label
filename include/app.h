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
        Serial.println(F("Start app"));
        display->initR(INITR_BLACKTAB); 
        display->setRotation(0);
        display->fillScreen(BACKGROUND_COLOR);

        display->println(F("Initilize lan.."));
        // container->getLan()->init();
        // container->getMemberService()->init();

        display->println(F("Initilize GPS.."));
        // container->getGPS()->init();

        buttons->setup();
        display->fillScreen(BACKGROUND_COLOR);

        start(header);
        start(current);
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
        // container->getMemberService()->update();
        // container->getGPS()->update();
    }

    
    void readPackages() {
        if (container->getLan()->available()) {
            Package pack = container->getLan()->read();
            if (pack.validate()) {
                container->getMemberService()->registerPakage(&pack);
            }
        }
    }

    uint16_t check_time = 0;

    void loop() {
        if (millis() - check_time > 100) {
            check_time = millis(); 
            header->check();
            current->check();
        }

        buttons->check();        

        // update every 1s 
         if (millis() - timing > 1000) {
            timing = millis(); 
            tasks();
        }
        

        // readPackages();
    }
};
