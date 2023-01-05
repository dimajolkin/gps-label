#pragma once
#include <vector>

class TaskManager
{
private:
    Thread *headerTask;
    Thread *gpsTask;
    Thread *batteryTask;

public:
    TaskManager()
    {
        headerTask = new Thread();
        gpsTask = new Thread();
        batteryTask = new Thread();
    }

    void registerHeaderTask(mbed::Callback<void()> task)
    {
        headerTask->start(task);
    }

    void registerGps(mbed::Callback<void()> task)
    {
        gpsTask->start(task);
    }

    void registerBattery(mbed::Callback<void()> task)
    {
        batteryTask->start(task);
    }
};