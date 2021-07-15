#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/members.h"
#include "app/view/members.h"

class MembersPage : public Page
{
private:
    MembersModel *model;

public:
    MembersPage(ServiceLocator *container) : Page(container)
    {
        model = new MembersModel(container->getMemberService()->getList());
        view = new MembersView(model);
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