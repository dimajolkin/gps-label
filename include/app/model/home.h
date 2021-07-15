#pragma once

#include "framework/ui/model.h"

class HomeModel : public Model
{
public:
    const static uint8_t DEFAULT_RADIUS_STEP = 10;
    const static uint8_t MAX_RADIUS_STEP = 30;
    const static uint8_t MAX_RADIUS = 70;
    uint8_t radiusStep = DEFAULT_RADIUS_STEP;

    void up()
    {
        radiusStep += DEFAULT_RADIUS_STEP;
        if (radiusStep > MAX_RADIUS_STEP)
        {
            radiusStep = MAX_RADIUS_STEP;
        }
    }

    void down()
    {
        radiusStep -= DEFAULT_RADIUS_STEP;
        if (radiusStep < DEFAULT_RADIUS_STEP)
        {
            radiusStep = DEFAULT_RADIUS_STEP;
        }
    }
};