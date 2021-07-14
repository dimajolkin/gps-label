#pragma once

#include "lib/ui/controller.h"
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

    Controller* onClick(uint8_t key)
    {
        if (key == Keyboard::KEY_UP) {
            menu->up();
        }

        if (key == Keyboard::KEY_DOWN) {
            menu->down();
        }

        if (key == Keyboard::KEY_OK) {
            return this;
        }
        
        view->refresh();
        
        return this;
    }
};
