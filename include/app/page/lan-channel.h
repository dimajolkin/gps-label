#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/lan-channel.h"
#include "app/view/lan-channel.h"

class LanChannelPage : public Page
{
private:
    LanChannelModel *model;

public:
    LanChannelPage(ServiceLocator *container) : Page(container)
    {
        model = new LanChannelModel();
        view = new LanChannelView(model);
    }

    Response *onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::LEFT)
        {
            return toBack();
        }

        return render(view);
    }
};