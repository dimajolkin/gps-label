#pragma once

#include "mbed.h"
#include <TinyGPSplus.h>

class GPSData  {
    public:
        double lat;
        double lng;
        GPSData(double lat, double lng): lat(lat), lng(lng) {}
};

class GPSDevice {
    private:
        BufferedSerial *serial;
        TinyGPSPlus *service;
        GPSData *data = NULL;
        char read_buffer[1] = {0};
        uint8_t initialize = 0;
    public:
        GPSDevice(PinName rx, PinName tx) {
            serial = new BufferedSerial(tx, rx, 9600);
            service = new TinyGPSPlus();
            data = new GPSData(0.0, 0.0);
        }

        void init() {
            while (!serial->readable()) {
                thread_sleep_for(500);
            }
            initialize = 1;
        }
     
        uint8_t getCountSatellites() {
            return (service->satellites).value();
        }

        GPSData* get() {
            return data;
        }

        BufferedSerial* getSerial() {
            return serial;
        }

        uint8_t isInit() {
            return initialize;
        }

        void read() {
            if (serial->read(&read_buffer, sizeof(char))) {
                if (service->encode(read_buffer[0])) {
                    auto location = service->location;
                    if (location.isValid()) {
                        data = new GPSData(location.lat(), location.lng());
                    }
                }
            }
        }
};