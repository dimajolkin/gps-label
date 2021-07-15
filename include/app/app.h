#include <mbed.h>
#include "service-locator.h"
#include "framework/ui/response.h"
#include "framework/ui/page.h"
#include "framework/ui/stack-page.h"
#include "framework/ui/render.h"

#include "app/page/test-page.h"
#include "app/page/menu-page.h"

class App
{
protected:
    ServiceLocator *container;
    StackPage *stack;
    View *view;
    Render *render;

public:
    App(ServiceLocator *container) : container(container)
    {
        render = new Render(container->getDisplay());
    }

    void onClick(Keyboard::KEY key)
    {
        Response *response = stack->getCurrent()->onClick(key);
        if (response->getPage())
        {
            stack->append(response->getPage());
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
        stack = new StackPage(
            new MenuPage(container)
        );

        render->setView(stack->getCurrent()->getView());
    }
};