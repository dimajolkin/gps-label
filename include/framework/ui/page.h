#pragma once

#include "service-locator.h"
#include "hardware/keyboard/keyboard.h"
#include "framework/ui/view.h"
#include "framework/ui/response.h"

class Page
{
protected:
    ServiceLocator *container;
    View *view;

    Response *redirect(Page *newPage)
    {
        return new ObjectResponse<Page>(newPage, Response::CODE::REDIRECT);
    }

    Response *render(View *view)
    {
        return new ObjectResponse<View>(view, Response::CODE::RENDER);
    }

    Response *toBack()
    {
        return new Response(Response::CODE::BACK);
    }
    
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