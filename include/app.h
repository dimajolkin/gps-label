#include "header/header.h"

#include "view/base-view.h"
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

    public:
    App(Adafruit_ST7735 *display) {
        header = new Header(display);
        buttons = new Buttons(BUTTON_PINS);

        current = new Home(display, header->getDy());
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

        if (current->getNext() != NULL) {
            current = current->getNext();
            refresh();
        }
    }

    void loop() {
        header->check();
        buttons->check();
        current->tick();
    }
};
