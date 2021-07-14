#pragma once

#include "lib/ui/controller.h"
#include "lib/ui/response.h"
#include "ui/model/menu.h"
#include "ui/view/menu.h"

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
