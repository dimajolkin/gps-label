#pragma once

#include "mbed.h"
#include <TinyGPSplus.h>

// using namespace mbed;

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
            while (!serial->readable()) {};
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

//         void TimePrint()
// {
//   if (gps.time.isValid())
//   {
//     if (gps.time.hour() < 10)
//       Serial.print(F("0"));
//     Serial.print(gps.time.hour());
//     Serial.print(F(":"));
//     if (gps.time.minute() < 10)
//       Serial.print(F("0"));
//     Serial.print(gps.time.minute());
//     Serial.print(F(":"));
//     if (gps.time.second() < 10)
//       Serial.print(F("0"));
//     Serial.print(gps.time.second());
//     Serial.print(F(" "));
//   }
//   else
//   {
//     Serial.print(F("(unknown)"));
//   }
// }
};