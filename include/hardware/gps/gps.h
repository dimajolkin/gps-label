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

#define MAXIMUM_BUFFER_SIZE  32

class GPSDevice {
    private:
        UnbufferedSerial *ss;
        TinyGPSPlus *gps;
        GPSData *data = NULL;
        char c[MAXIMUM_BUFFER_SIZE];
    public:
        GPSDevice(PinName rx, PinName tx) {
            ss = new UnbufferedSerial(tx, rx, 9600);
            gps = new TinyGPSPlus();
            data = new GPSData(0.0, 0.0);
        }

        void init() {
            while (!ss->readable()) {};
        }
     
        uint8_t getCountSatellites() {
            return (gps->satellites).value();
        }

        GPSData *get() {
            return data;
        }

        UnbufferedSerial* getSerial() {
            return ss;
        }

        void update() {
            if (ss->readable()) {
                ss->read(&c, MAXIMUM_BUFFER_SIZE);
                gps->encode(c[0]);
                auto location = gps->location;
                if (location.isValid()) {
                    data = new GPSData(location.lat(), location.lng());
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