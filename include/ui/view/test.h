#pragma once

#include "hardware/display/display.h"
#include "ui/model/test-model.h"
#include "ui/view/view.h"

class TestView : public View
{
private:
    const static uint8_t FLAG_REFRESH = 1;

    TestModel *model;
    EventFlags *refreshFlag;

public:
    TestView(TestModel *model) : model(model) {
        refreshFlag = new EventFlags();
    }

    void draw(Display *display)
    {
        refreshFlag->wait_any(FLAG_REFRESH);
        refreshFlag->clear();

        display->fillScreen(ST7735_GREEN);
        display->setTextCursor(10, 10);
        display->setTextColor(ST7735_BLACK);
        display->setTextSize(1);
        display->setTextWrap(true);
        for (uint16_t i = 0; i < 5; i++)
        {
            display->setTextCursor(10, 20 * i);
            display->printf("%d) - %d \n", i, model->counts[i]);
        }

        display->printf("Packages: %d \n", model->countPackages);
    }

    void refresh()
    {
        refreshFlag->set(FLAG_REFRESH);
    }
};