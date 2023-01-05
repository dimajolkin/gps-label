#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/menu.h"
#include "app/view/menu.h"
#include "app/page/test.h"
#include "app/page/lan-channel.h"
#include "app/page/members.h"
#include "app/page/change-my-member-number.h"
#include "app/page/gps.h"

class MenuPage : public Page
{
private:
    MenuModel *menu;

public:
    MenuPage(Container *container) : Page(container)
    {
        menu = new MenuModel();
        view = new MenuView(menu);
    }

    Response *onClick(Keyboard::KEY key)
    {
        if (key == Keyboard::KEY::UP)
        {
            menu->up();
        }

        if (key == Keyboard::KEY::DOWN)
        {
            menu->down();
        }

        if (key == Keyboard::KEY::LEFT)
        {
            return toBack();
        }

        if (key == Keyboard::KEY::OK)
        {
            if (menu->isActive(MenuElementEnum::LAN_CHANNEL))
            {
                return redirect(new LanChannelPage(container));
            }
            if (menu->isActive(MenuElementEnum::MEMBERS))
            {
                return redirect(new MembersPage(container));
            }
            if (menu->isActive(MenuElementEnum::CHANGE_MY_MEMBER_NUMBER))
            {
                return redirect(new ChangeMyMemberNumberPage(container));
            }
            if (menu->isActive(MenuElementEnum::TEST))
            {
                return redirect(new TestPage(container));
            }
            if (menu->isActive(MenuElementEnum::GPS))
            {
                return redirect(new GpsPage(container));
            }

            error("not found menu element");
        }

        return render(view);
    }
};
