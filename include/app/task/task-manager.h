#pragma once
#include <vector>

class TaskManager
{
// private:
    // std::vector list;

public:
    TaskManager()
    {
    }

    void append(mbed::Callback<void()> task)
    {
        Thread t;
        t.start(task);

        // list.append(t);
    }
};