#pragma once

#include <mbed.h>
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

    void drawWait(const char *str)
    {
        auto display = container->getDisplay();
        char p[] = ".....";
        for (uint8_t i = 0; i< 10; i++)
        {
            for (uint8_t n = 0; n < 5; n++)
            {
                for (uint8_t k = 0; k < 5; k++)
                {
                    p[k] = (k < n) ? '.' : ' ';
                }
                
                display->printf(str, p);

                thread_sleep_for(500);
                display->clearText(20);
            }
        } 
    }

    void loading(const char *text, mbed::Callback<bool()> task)
    {
        auto display = container->getDisplay();
        Thread taskLoadingGps;
        taskLoadingGps.start([this] {
            this->drawWait("\rGPS: %s");
        });
        thread_sleep_for(2000);

        while (true)
        {
            if (task()) {
                taskLoadingGps.terminate();
                break;
            }
            thread_sleep_for(100);
        }

        display->clearText(10);

        display->printf("GPS: ");
        display->setTextColor(ST7735_GREEN);
        display->printf("DONE \n");
    
        display->setTextColor(ST7735_WHITE);
    }

    void bootstrap()
    {
        auto display = container->getDisplay();
        display->init();
        display->setTextCursor(0, 0);
        display->setTextColor(ST7735_WHITE);
        display->printf("Initialization devices: \n");
        
        auto gps = this->container->getGPS();
        this->loading("GPS", [this, gps] {
            gps->init();

            return gps->isInit();
        }); 
        
        this->loading("LAN", [this, gps] {
            gps->init();

            return gps->isInit();
        });
       
       
        // display->setTextColor(ST7735_YELLOW);
        // display->printf("WAIT");
        // 

        // display->clearText(10, 5);
        // display->setTextColor(ST7735_RED);
        // display->printf("FAILED");

        
    }

    void init()
    {
        this->bootstrap();

        return;
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