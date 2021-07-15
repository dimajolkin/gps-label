#pragma once

#include "framework/ui/page.h"
#include "framework/ui/view.h"

class Response
{
protected:
    Page *page = NULL;
    View *view = NULL;

public:
    Response(Page *page) : page(page) {}
    Response(View *view) : view(view) {}

    Page *getPage()
    {
        return page;
    }

    View *getView()
    {
        return view;
    }
};