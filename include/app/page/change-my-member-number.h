#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/view/change-my-member-number.h"
#include "app/model/change-my-member-number.h"
#include "device/member-service.h"

class ChangeMyMemberNumberPage : public Page
{
private:
    ChangeMyMemberNumberModel *model;
    MemberService *service;

public:
    ChangeMyMemberNumberPage(ServiceLocator *container) : Page(container)
    {
        service = container->getMemberService();
        uint8_t number = service->getMy()->getNumber();
        model = new ChangeMyMemberNumberModel(number);
        view = new ChangeMyMemberNumberPageView(model);
    }

    Response *onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::OK)
        {
            service->updateMyNumber(model->getNumber());
            return toBack();
        }

        if (key == Keyboard::KEY::LEFT)
        {
            return toBack();
        }

        if (key == Keyboard::KEY::UP)
        {
            model->up();
        }

        if (key == Keyboard::KEY::DOWN)
        {
            model->down();
        }

        return render(view);
    }
};