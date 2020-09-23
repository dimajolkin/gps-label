#include "header/header.h"
#include "view/base-view.h"
#include "view/menu.h"
#include "view/home.h"

class App {
    private:
        Header *header;
        BaseView *current;
        Buttons *buttons;

    public:
    App(Adafruit_ST7735 *display) {
        header = new Header(display);
        current = new Home(display, header->getDy());
        buttons = new Buttons(BUTTON_PINS);
    }

    void setup() {
        buttons->setup();
        refresh();
    }

    void refresh() {
        current->setup();
        header->setup();
    }

    void registerHandlerKeyboard(ButtonConfig::EventHandler handleEvent) {
        buttons->setEventHandler(handleEvent);
    }

    void onClick(uint8_t btn) {
        current->onClick(btn);
        Serial.println("click");

        if (current->getNext() != NULL) {
            BaseView *next = current->getNext();
            next->SetPreview(current);
            // current->SetNext(NULL);
            current = next;
            refresh();
        }
    }

    void loop() {
        header->check();
        buttons->check();
        current->tick();
    }
};
