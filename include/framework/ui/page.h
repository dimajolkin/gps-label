#pragma once

#include "app/container.h"
#include "board/hardware/keyboard/keyboard.h"
#include "framework/ui/view.h"
#include "framework/ui/response.h"
#include "framework/ui/render.h"

class Page
{
protected:
    Container *container;
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

    void refresh()
    {
        container->getRender()->setContentView(view);
    }
    
public:
    Page(Container *container) : container(container) {}

    virtual ~Page()
    {
        delete view;
    }

    View *getView()
    {
        return view;
    }

    virtual Response *onClick(Keyboard::KEY key) = 0;
};