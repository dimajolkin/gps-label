#pragma once

#include "mbed.h"
// #include <BufferedSerial.h>
#include <TinyGPSplus.h>

// using namespace mbed;

class GPSData  {
    public:
        double lat;
        double lng;
        GPSData(double lat, double lng): lat(lat), lng(lng) {}
};

class GPS {
    private:
        BufferedSerial *ss;
        TinyGPSPlus *gps;
        GPSData *data = NULL;
    public:
        GPS(PinName rx, PinName tx) {
            // ss = new BufferedSerial(rx, tx, 9600);
            gps = new TinyGPSPlus();
            data = new GPSData(0.0, 0.0);
        }

        void init() {
            // while (!ss->readable()) {};
        }
     
        uint8_t getCountSatellites() {
            return (gps->satellites).value();
        }

        GPSData *get() {
            return data;
        }

        void update() {
            // if (ss->readable()) {
                // gps->encode(ss->read());
                // data = new GPSData(
                    // (gps->location).lat(),
                    // (gps->location).lat()
                // );
            // }
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