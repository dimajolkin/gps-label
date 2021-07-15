#pragma once

#include "service-locator.h"
#include "hardware/keyboard/keyboard.h"
#include "framework/ui/view.h"
#include "framework/ui/response.h"

class Response;

class Page
{
protected:
    ServiceLocator *container;
    View *view;

public:
    Page(ServiceLocator *container) : container(container) {}

    virtual ~Page()
    {
        delete (view);
    }

    View *getView()
    {
        return view;
    }

    virtual Response *onClick(Keyboard::KEY key) = 0;
};