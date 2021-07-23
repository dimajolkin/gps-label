#pragma once

#include "framework/ui/page.h"
#include "app/model/header.h"

class HeaderPage : public Page
{
private:
    HeaderModel *model;

public:
    HeaderPage(ServiceLocator *container) : Page(container)
    {
        model = new HeaderModel(container);
        view = new HeaderView(model);
    }

    Response *onClick(Keyboard::KEY key) {
        return render(view);
    }
};
