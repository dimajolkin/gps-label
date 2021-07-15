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

    void append(Page* contr)
    {
        stack.push_back(contr);
    }
};