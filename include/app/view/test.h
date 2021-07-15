#pragma once

#include "hardware/display/display.h"
#include "app/model/test-model.h"
#include "framework/ui/view.h"

class TestView : public View
{
protected:
    uint8_t refFlag = 3;

private:
    TestModel *model;

public:
    TestView(TestModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        printf("--- render test view \n");

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
};