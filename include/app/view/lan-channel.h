#pragma once

#include "hardware/display/display.h"
#include "app/model/lan-channel.h"
#include "framework/ui/view.h"

class LanChannelView : public View
{
private:
    LanChannelModel *model;

public:
    LanChannelView(LanChannelModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->setTextCursor(0, 10);
        display->printf("--- render lan channel view \n");
        printf("--- render lan channel view \n");
        printf("--- render lan channel view \n");
    }
};