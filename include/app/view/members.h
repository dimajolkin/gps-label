#pragma once

#include "hardware/display/display.h"
#include "app/model/members.h"
#include "framework/ui/view.h"

class MembersView : public View
{
private:
    MembersModel *model;

public:
    MembersView(MembersModel *model) : View(), model(model) {}

    void update(Display *display)
    {
        display->setTextCursor(0, 10);
        display->printf("--- render members view \n");
        printf("--- render members view \n");
    }
};