#include <mbed.h>
#include "service-locator.h"
#include "framework/ui/response.h"
#include "framework/ui/page.h"
#include "framework/ui/stack-page.h"
#include "framework/ui/render.h"

#include "app/view/layout-view.h"
#include "app/page/test-page.h"
#include "app/page/menu-page.h"

class App
{
protected:
    ServiceLocator *container;
    StackPage *stack;
    View *view;
    Render *render;

    void route(Response *response)
    {
        if (response->getCode() == Response::CODE::BACK)
        {
            stack->removeBack();
            render->clear();
            render->setContentView(stack->getCurrent()->getView());
        }

        if (response->getCode() == Response::CODE::RENDER)
        {
            auto objectResponse = static_cast<ObjectResponse<View> *>(response);
            render->setContentView(objectResponse->getObject());
        }

        if (response->getCode() == Response::CODE::REDIRECT)
        {
            auto objectResponse = static_cast<ObjectResponse<Page> *>(response);
            stack->append(objectResponse->getObject());
            render->clear();
            render->setContentView(stack->getCurrent()->getView());
        }
    }

public:
    App(ServiceLocator *container) : container(container)
    {
        render = new Render(
            container->getDisplay(),
            new LayoutView(
                new HeaderView()));
    }

    void onClick(Keyboard::KEY key)
    {
        Response *response = stack->getCurrent()->onClick(key);
        route(response);
    }

    void init()
    {
        container->getKeyboard()->init();
        container->getLogger()->init();

        container->getDisplay()->initR(INITR_BLACKTAB);
        container->getDisplay()->setRotation(0);
        render->run();

        stack = new StackPage(
            new MenuPage(container));

        render->clear();
        render->setContentView(stack->getCurrent()->getView());
    }
};