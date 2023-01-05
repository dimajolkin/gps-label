#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/test.h"
#include "app/view/test.h"

class TestPage : public Page
{
private:
    TestModel *testModel;
    Thread *lanThread;

public:
    TestPage(Container *container) : Page(container)
    {
        testModel = new TestModel();
        view = new TestView(testModel);
        lanThread = new Thread();
        lanThread->start(callback(this, &TestPage::onLanThread));
    }

    ~TestPage() {
        lanThread->terminate();
        delete lanThread;
    }

    void onLanThread()
    {
        Lan *lan = container->getLan();
        while (true)
        {
            if (lan->available())
            {
                Package p = lan->read();
                if (p.validate())
                {
                    testModel->countPackages++;
                    refresh();
                }
            }
            thread_sleep_for(100);
        }
    }

    Response *onClick(Keyboard::KEY key)
    {
        testModel->click((uint8_t)key);
        printf("inc model %i %i \n", key, testModel->count(key));
        if (key == Keyboard::KEY::LEFT)
        {
            return toBack();
        }

        return render(view);
    }
};