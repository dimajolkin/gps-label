#pragma once

#include "board/hardware/display/display.h"
#include "app/model/gps.h"
#include "framework/ui/view.h"

class GpsView : public View
{
private:
    GpsModel *model;
    uint8_t n = 0;

public:
    GpsView(GpsModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->fillScreen(BACKGROUND_COLOR);
        n++;
        display->setTextCursor(0, 15);
        GPSData *data = model->get();
        display->printf("Tick: %i \n", n);
        display->printf("Satellites: %i \n", model->getSatellites());
        display->printf("Lat: %f\n", data->lat);
        display->printf("Lng: %f\n", data->lng);
    }
};