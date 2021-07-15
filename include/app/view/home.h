#pragma once

#include "hardware/display/display.h"
#include "app/model/home.h"
#include "framework/ui/view.h"

class HomeView : public View
{
private:
    HomeModel *model;

public:
    HomeView(HomeModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->setTextCursor(0, 10);
        display->printf("--- render home view \n");
    }
};