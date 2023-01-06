#pragma once

#include "board/board.h"

#define CLEAR_TEXT_SIZE 12

class BootApp
{
private:
    Board *board;

    void drawWait(std::string name)
    {
        auto display = board->getDisplay();
        char p[] = ".....";
        for (;;)
        {
            for (uint8_t n = 0; n < 5; n++)
            {
                for (uint8_t k = 0; k < 5; k++)
                {
                    p[k] = (k < n) ? '.' : ' ';
                }

                display->printf(std::string("\r" + name).c_str(), p);

                thread_sleep_for(500);
                display->clearText(CLEAR_TEXT_SIZE);
            }
        }
    }

    void loading(const char *name, mbed::Callback<bool()> check)
    {
        loading(name, [] {}, check);
    }

    void loading(const char *name, mbed::Callback<void()> init, mbed::Callback<bool()> check)
    {
        auto display = board->getDisplay();
        Thread taskLoadingGps;
        taskLoadingGps.start([this, name]
                             {
                                 this->drawWait(std::string(name).append(": %s"));
                             });

        thread_sleep_for(500);
        init();
        while (true)
        {
            if (check())
            {
                taskLoadingGps.terminate();
                break;
            }
            thread_sleep_for(100);
        }

        display->clearText(CLEAR_TEXT_SIZE);
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
        display->setTextSize(2);
        display->setTextCursor(0, 0);
        display->setTextColor(ST7735_WHITE);
        display->printf("Run GPS-LABEL v1.0: \n");

        auto gps = this->board->getGPS();
        this->loading("GPS", callback(gps, &GPSDevice::init), [this, gps] {
            return gps->isInit();
        }); 
        
        auto storage = this->board->getStorage();
        this->loading("FLASH", [this, storage] {
            storage->write(200, 12);
            if (storage->read(200) == 12) {
                storage->write(200, 0);
                return true;
            }

            return false;
        });

        auto lan = this->board->getLanIn();
        this->loading("LAN-IN", callback(lan, &Lan::init), [this, lan] {
            return lan->isEnable();
        });
        display->printf("SUCCESS");
    }
};