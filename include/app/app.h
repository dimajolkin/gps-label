#pragma once

#include <mbed.h>
#include <string>
#include "service-locator.h"
#include "framework/ui/response.h"
#include "framework/ui/page.h"
#include "framework/ui/stack-page.h"
#include "framework/ui/render.h"
#include "app/view/header/header.h"
#include "app/page/home.h"

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

    HeaderModel *headerModel;
    // move in task manager
    void taskHeader() {
        while(true) {
            headerModel->update();
            thread_sleep_for(1000 * 2);
        }
    }

    Thread *headerThread;

public:
    App(ServiceLocator *container) : container(container) {
        headerModel = new HeaderModel(container);
        headerThread = new Thread();
        headerThread->start(callback(this, &App::taskHeader));
        
        render = new Render(container->getDisplay(), new HeaderView(headerModel));
        container->setRender(render);
    }

    void onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::OK)
        {
            container->getRender()->clear();
        }

        Response *response = stack->getCurrent()->onClick(key);
        route(response);
    }

    void init()
    {
        container->getKeyboard()->onKeyPress(callback(this, &App::onClick));
        container->getKeyboard()->init();
        container->getLogger()->init();
        // container->getMemberService()->init();
        // container->getLan()->init();
        // container->getGPS()->init();

        container->getRender()->init();        
        printf("Display: %ix%i \n", container->getDisplay()->width(), container->getDisplay()->height());
        stack = new StackPage(
            new HomePage(container)
        );

        render->clear();
        render->setContentView(stack->getCurrent()->getView());
    }
};