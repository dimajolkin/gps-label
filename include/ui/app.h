#include <mbed.h>
#include "service-locator.h"
#include "ui/view/test.h"
#include "ui/model/test-model.h"
#include "lib/ui/controller.h"
#include "lib/ui/stack-controller.h"
#include "ui/controller/test-controller.h"
#include "ui/controller/menu-controller.h"

class App
{
protected:
    ServiceLocator *container;
    StackController *stack;
    EventFlags *refreshFlag;
public:
    App(ServiceLocator *container) : container(container) {
        refreshFlag = new EventFlags();
    }

    void draw()
    {
        View *view = stack->getCurrent()->getView();
        view->draw(container->getDisplay());
    }

    void onClick(uint8_t key)
    {
        Controller *contr = stack->getCurrent()->onClick(key);

        // Controller *contr2 = new TestController(container);
    }

    void init()
    {
        container->getDisplay()->initR(INITR_BLACKTAB);
        container->getDisplay()->setRotation(0);
        container->getDisplay()->fillScreen(ST7735_RED);
        
        // controller = new TestController(container);
        stack = new StackController(
            new TestController(container)
        );
    }
};