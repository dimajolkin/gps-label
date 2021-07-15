#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/menu.h"
#include "app/view/menu.h"

class MenuPage : public Page
{
private:
    MenuModel *menu;

public:
    MenuPage(ServiceLocator *container) : Page(container)
    {
        menu = new MenuModel();
        view = new MenuView(menu);
    }

    Response* onClick(uint8_t key)
    {
        printf("menu click \n");
        
        if (key == Keyboard::KEY_UP) {
            menu->up();
        }

        if (key == Keyboard::KEY_DOWN) {
            menu->down();
        }

        if (key == Keyboard::KEY_OK) {
            return new Response(new TestPage(container));
        }
        
        return new Response(view);
    }
};
