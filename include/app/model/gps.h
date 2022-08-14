#pragma once

#include "framework/ui/model.h"

class GpsModel : public Model
{
    private:
        GPSDevice *device;

    public:
        GpsModel(GPSDevice *device): device(device) {}

    uint8_t getSatellites() {
        return device->getCountSatellites();
    }
    
    GPSData* get() {
        return device->get();
    }
};