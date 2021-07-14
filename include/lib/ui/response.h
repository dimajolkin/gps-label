#pragma once

#include "lib/ui/controller.h"
#include "lib/ui/view.h"

class Response
{
protected:
    Controller *controller = NULL;
    View *view = NULL;

public:
    Response(Controller *controller) : controller(controller) {}
    Response(View *view) : view(view) {}

    Controller *getController()
    {
        return controller;
    }

    View *getView()
    {
        return view;
    }
};