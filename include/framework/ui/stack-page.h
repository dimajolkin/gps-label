#pragma once

#include "framework/ui/page.h"
#include <vector>

class StackPage
{
private:
    std::vector<Page*> stack;

public:
    StackPage(Page *current) {
        stack.push_back(current);
    }

    Page *getCurrent()
    {
        return stack.back();
    }

    void append(Page* page)
    {
        stack.push_back(page);
    }

    void removeBack()
    {
        stack.pop_back();
    }
};