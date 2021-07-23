#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/members.h"
#include "app/view/members.h"

class MembersPage : public Page
{
private:
    MembersModel *model;
    Thread *thread;

public:
    MembersPage(ServiceLocator *container) : Page(container)
    {
        model = new MembersModel(container->getMemberService()->getList());
        view = new MembersView(model);
        thread = new Thread();
        thread->start(callback(this, &MembersPage::onTask));
    }


    ~MembersPage() {
        thread->terminate();
        delete thread;
    }

    void onTask()
    {
        while (true) {
            refresh();
            thread_sleep_for(500);
        }
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