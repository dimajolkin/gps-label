#pragma once

#include "board/board.h"

class BootApp
{
private:
    Board *board;

    void drawWait(std::string name)
    {
        auto display = board->getDisplay();
        char p[] = ".....";
        for (uint8_t i = 0; i < 10; i++)
        {
            for (uint8_t n = 0; n < 5; n++)
            {
                for (uint8_t k = 0; k < 5; k++)
                {
                    p[k] = (k < n) ? '.' : ' ';
                }

                // display->printf(strcat("\r", name), p);
                display->printf(std::string("\r" + name).c_str(), p);

                thread_sleep_for(500);
                display->clearText(20);
            }
        }
    }

    void loading(const char *name, mbed::Callback<bool()> task)
    {
        auto display = board->getDisplay();
        Thread taskLoadingGps;
        taskLoadingGps.start([this, name]
                             {
                                 this->drawWait(std::string(name).append(": %s"));
                                 // this->drawWait(strcat(name, ": %s"));
                             });
        thread_sleep_for(2000);

        while (true)
        {
            if (task())
            {
                taskLoadingGps.terminate();
                break;
            }
            thread_sleep_for(100);
        }

        display->clearText(10);

        display->printf(std::string(name).append(": ").c_str());
        display->setTextColor(ST7735_GREEN);
        display->printf("DONE \n");

        display->setTextColor(ST7735_WHITE);
    }

public:
    BootApp(Board *board) : board(board)
    {
    }

    void run()
    {
        auto display = board->getDisplay();
        display->init();
        display->setTextCursor(0, 0);
        display->setTextColor(ST7735_WHITE);
        display->printf("Initialization devices: \n");
        
        auto gps = this->board->getGPS();
        this->loading("GPS", [this, gps] {
            gps->init();

            return gps->isInit();
        }); 
        

        this->loading("LAN", [this, gps] {
            gps->init();

            return gps->isInit();
        });
       
    }
};