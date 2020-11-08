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
        Package *lastPackage = NULL;
        
    public:
    App(Display *display, Container *container): display(display), container(container) {
        header = new Header(display);
        buttons = new Buttons(BUTTON_PINS);
        current = new MapPage(display, header->getDy() + 1);
    }

    void setup() {
        container->getLogger()->start();
        // container->getLogger()->attachDisplay(display);
        container->getLogger()->attachSerial();

        Serial.println(F("Start app"));

        display->initR(INITR_BLACKTAB); 
        display->setRotation(0);
        display->fillScreen(BACKGROUND_COLOR);
        display->println(F("Wait initilize..."));
       // initialize

        Lan *lan = container->getLan();
        lan->init();

        // режим согласования номеров 
        container->getMembers()->append(new Member(1, true));

        //
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

    void loop() {
        header->check();
        buttons->check();
        current->check();
        
        if (container->getLan()->available()) {
            Package pack = container->getLan()->read();
            if (pack.validate()) {
                lastPackage = &pack;

                Serial.println(lastPackage->n);
                Serial.println(lastPackage->getLan());
                Serial.println(lastPackage->getLng());
                Serial.println(F("===== "));
                container->getMembers()->registerPakage(lastPackage);

            } else {
                 Serial.println(F("Failed..."));
            }
        }
    }
};
