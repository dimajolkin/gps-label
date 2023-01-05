#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/page/menu.h"
#include "app/model/home.h"
#include "app/view/home.h"

class HomePage : public Page
{
private:
    HomeModel *model;

public:
    HomePage(Container *container) : Page(container)
    {
        model = new HomeModel();
        view = new HomeView(model);
    }

    Response *onClick(Keyboard::KEY key)
    {
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
            return redirect(new MenuPage(container));
        }

        return render(view);
    }
};