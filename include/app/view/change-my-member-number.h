#pragma once

#include "hardware/display/display.h"
#include "app/model/change-my-member-number.h"
#include "framework/ui/view.h"

class ChangeMyMemberNumberPageView : public View
{
private:
    ChangeMyMemberNumberModel *model;

public:
    ChangeMyMemberNumberPageView(ChangeMyMemberNumberModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->fillScreen(BACKGROUND_COLOR);
        display->setTextColor(ST7735_WHITE);
        display->setTextCursor(1, 30);
        display->setTextSize(12);
        display->printf("%i\n", model->getNumber());
    }
};