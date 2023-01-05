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
    LanChannelPage(Container *container) : Page(container)
    {
        model = new LanChannelModel(container->getLanIn()->getConfig()->getChannel());
        view = new LanChannelView(model);
    }

    Response *onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::RIGHT)
        {
            model->next();
        }

        if (key == Keyboard::KEY::LEFT)
        {
            model->back();
        }

        if (key == Keyboard::KEY::UP)
        {
            model->up();
        }

        if (key == Keyboard::KEY::DOWN)
        {
            model->down();
        }

        if (key == Keyboard::KEY::OK)
        {
            container->getLanIn()->getConfig()->setChannel(model->getSelected());
            return toBack();
        }

        return render(view);
    }
};