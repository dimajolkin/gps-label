#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/gps.h"
#include "app/view/gps.h"

class GpsPage : public Page
{
private:
    GpsModel *model;

public:
    GpsPage(ServiceLocator *container) : Page(container)
    {
        model = new GpsModel();
        view = new GpsView(model);
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