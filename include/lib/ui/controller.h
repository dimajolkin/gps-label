#pragma once

#include "service-locator.h"
#include "lib/ui/view.h"
#include "lib/ui/response.h"

class Response;

class Controller
{
protected:
    ServiceLocator *container;
    View *view;

public:
    Controller(ServiceLocator *container) : container(container) {}

    virtual ~Controller()
    {
        delete (view);
    }

    View *getView()
    {
        return view;
    }

    virtual Response *onClick(uint8_t key) = 0;
};