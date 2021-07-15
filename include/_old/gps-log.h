#pragma once

#include "lib/page/page.h"

class GPSLog: public Page {
    private:
        Container *container;
    public:
        GPSLog(Display *display, uint8_t dy): Page(display, dy) {}

        void configure(Container *container) {
            container = container;
        }

        void onClick(uint8_t btn) {
            if (btn == BTN_LEFT) {
                goBack();
                return;
            }
        }
     
        void render() {
            
        }

        void update () {
            clear();
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