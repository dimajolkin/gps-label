#include <mbed.h>
#include "service-locator.h"
#include "ui/view/test.h"
#include "ui/model/test-model.h"
#include "ui/controller/controller.h"
#include "ui/controller/test-controller.h"

class App
{

protected:
    ServiceLocator *container;
    Controller *controller;

public:
    App(ServiceLocator *container) : container(container) {}

    void draw()
    {
        if (controller)
        {
            controller->draw();
        }
    }

    void onClick(uint8_t key)
    {
        if (controller)
        {
            // container->getLogger()->printf("test \n");
            controller->onClick(key);
        }
    }

    void init()
    {
        container->getDisplay()->initR(INITR_BLACKTAB);
        container->getDisplay()->setRotation(0);
        container->getDisplay()->fillScreen(ST7735_RED);

        controller = new TestController(container);
    }
};