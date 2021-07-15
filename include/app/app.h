#include <mbed.h>
#include "service-locator.h"
#include "framework/ui/response.h"
#include "framework/ui/controller.h"
#include "framework/ui/stack-controller.h"
#include "framework/ui/render.h"

#include "app/controller/test-controller.h"
#include "app/controller/menu-controller.h"

class App
{
protected:
    ServiceLocator *container;
    StackController *stack;
    View *view;
    Render *render;
    EventFlags *refreshFlag;

public:
    App(ServiceLocator *container) : container(container)
    {
        render = new Render(container->getDisplay());
    }

    void onClick(uint8_t key)
    {
        Response *response = stack->getCurrent()->onClick(key);
        if (response->getController())
        {
            stack->append(response->getController());
            render->setView(stack->getCurrent()->getView());
        }

        if (response->getView())
        {
            render->setView(response->getView());
        }
    }

    void init()
    {
        render->run();
        container->getDisplay()->initR(INITR_BLACKTAB);
        container->getDisplay()->setRotation(0);
        container->getDisplay()->fillScreen(ST7735_RED);

        // controller = new TestController(container);
        stack = new StackController(
            new MenuController(container)
        );

        render->setView(stack->getCurrent()->getView());
    }
};