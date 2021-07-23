#pragma once

#include "framework/ui/model.h"

class LanChannelModel : public Model
{
public:
    static const uint8_t COUNT_CHANELS = 42; // 127
    static const uint8_t COUNT_BLOCKS_IN_LINE = 6;

private:
    uint8_t selected;
    uint8_t active;

    void check()
    {
        if (selected > COUNT_CHANELS)
        {
            selected = COUNT_CHANELS;
        }

        if (selected < 1)
        {
            selected = 1;
        }
    }

public:
    LanChannelModel(uint8_t _active) {
        active = _active;
        selected = _active;
    }

    bool isChange() {
        return selected != active;
    }

    uint8_t getSelected()
    {
        return selected;
    }

    uint8_t getActive()
    {
        return active;
    }

    void next()
    {
        selected++;
        check();
    }

    void back()
    {
        selected--;
        check();
    }

    void up()
    {
        selected -= COUNT_BLOCKS_IN_LINE;
        check();
    }

    void down()
    {
        selected += COUNT_BLOCKS_IN_LINE;
        check();
    }
};