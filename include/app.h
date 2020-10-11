#pragma once

#include "lib/view/renderer.h"
#include "lib/view/base-view.h"

#include "header/header.h"
#include "view/channel.h"
#include "view/test-view.h"
// #include ...
// added new view 

#include "view/setting.h"
#include "view/home.h"

class App {
    private:
        Header *header;
        BaseView *current;
        Buttons *buttons;
        Adafruit_ST7735 *display;
        Container *container;
        uint8_t stop = 0;
        
    public:
    App(Adafruit_ST7735 *display, Container *container): display(display), container(container) {
        header = new Header(display);
        buttons = new Buttons(BUTTON_PINS);
        current = new Home(display, header->getDy() + 1);
    }

    void exist() {
        stop = 1;
    }

    void setup() {
        display->initR(INITR_BLACKTAB); 
        display->setRotation(0);
        display->fillScreen(BACKGROUND_COLOR);
       // initialize
       
        Lan *lan = container->getLan();
        lan->init();

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
        container->getLan()->check();
    }
};
