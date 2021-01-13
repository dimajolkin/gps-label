#pragma once

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class GPSData  {
    public:
        double lat;
        double lng;
        GPSData(double lat, double lng): lat(lat), lng(lng) {}
};

class GPS {
    private:
        SoftwareSerial *ss;
        TinyGPSPlus *gps;
        GPSData *data = NULL;
    public:
        GPS(uint8_t rx, uint8_t tx) {
            ss = new SoftwareSerial(rx, tx);
            gps = new TinyGPSPlus();
            data = new GPSData(0.0, 0.0);
        }


        void init() {
            ss->begin(9600);
            while (!ss->available()) {};
        }
     
        uint8_t getCountSatellites() {
            return (gps->satellites).value();
        }

        GPSData *get() {
            return data;
        }

        void update() {
            if (ss->available()) {
                gps->encode(ss->read());
                data = new GPSData(
                    (gps->location).lat(),
                    (gps->location).lat()
                );
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