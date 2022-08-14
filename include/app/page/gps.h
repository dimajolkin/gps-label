#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/gps.h"
#include "app/view/gps.h"

class GpsPage : public Page
{
private:
    GpsModel *model;
    Thread *thread;
public:
    GpsPage(ServiceLocator *container) : Page(container)
    {
        model = new GpsModel(container->getGPS());
        view = new GpsView(model);
        thread = new Thread();
        thread->start(callback(this, &GpsPage::onTask));
    }

    ~GpsPage() {
        thread->terminate();
        delete thread;
    }

    void onTask()
    {
        while (true) {
            refresh();
            thread_sleep_for(1000); // 1s
        }
    }

    Response *onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::LEFT)
        {
            return toBack();
        }

        return render(view);
    }
};