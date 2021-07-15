#pragma once

#include "framework/ui/controller.h"
#include "framework/ui/response.h"
#include "app/model/menu.h"
#include "app/view/menu.h"

class MenuController : public Controller
{
private:
    MenuModel *menu;

public:
    MenuController(ServiceLocator *container) : Controller(container)
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
            return new Response(new TestController(container));
        }
        
        return new Response(view);
    }
};
