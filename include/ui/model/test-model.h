#pragma once

#include "lib/ui/model.h"

class TestModel : public Model
{
public:
    int counts[5] = {0, 0, 0, 0, 0};
    int countPackages = 0;

    int count(uint8_t key) {
        return counts[key];
    }
    void click(uint8_t key)
    {
        counts[key]++;
    }
};