#pragma once

#include "hardware/display/display.h"
#include "app/model/gps.h"
#include "framework/ui/view.h"

class GpsView : public View
{
private:
    GpsModel *model;

public:
    GpsView(GpsModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->setTextCursor(0, 10);
        display->printf("--- render gps view \n");
        printf("--- render gps view \n");
    }
};