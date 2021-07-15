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
        // display->setCursor(1, dy + 30);
        // GPSData *data = container->getGPS()->get();
        // display->print(F("Satellites: "));
        // display->println(container->getGPS()->getCountSatellites());
        // display->print(F("Lat: "));
        // display->println(data->lat);
        // display->print(F("Lng: "));
        // display->println(data->lng);
    }
};