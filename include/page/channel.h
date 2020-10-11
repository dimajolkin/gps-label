#pragma once

#include "lib/page/page.h"
#include "devices/lan/lan.h"

class ChannelPage: public Page {
    private:
        uint8_t active = 1;
        uint8_t selected = 1;
        static const uint8_t COUNT_CHANELS = 42; // 127
        static const uint8_t COUNT_BLOCKS_IN_LINE = 6;

        static const uint16_t BACKGROUND_BLOCK = ST7735_BLUE;
        static const uint16_t BACKGROUND_ACTIVE_BLOCK = ST7735_GREEN;
        static const uint16_t BACKGROUND_SELECT_BLOCK = ST7735_YELLOW;
        static const uint16_t BACKGROUND_DISABLE = ST7735_BLACK;
        Lan *lan;

        void drawSelect(uint8_t n, uint8_t previewNumber) {
            block(previewNumber);
            selectBlock(n);
        }

        void selectBlock(uint8_t n) {
            if (lan->isChannelActive(n)) {
                drawBlock(n, BACKGROUND_SELECT_BLOCK, BACKGROUND_BLOCK);
            } else {
                drawBlock(n, BACKGROUND_SELECT_BLOCK, BACKGROUND_DISABLE);
            }
        }

        void defaultBlock(uint8_t n) {
            drawBlock(n, BACKGROUND_BLOCK, BACKGROUND_BLOCK);
        }

        void disableBlock(uint8_t n) {
            drawBlock(n, BACKGROUND_DISABLE, BACKGROUND_DISABLE);
        }

        void block(uint8_t n) {
            if (n == active) {
                drawBlock(n, BACKGROUND_ACTIVE_BLOCK, BACKGROUND_BLOCK);
            } else if (lan->isChannelActive(n)) {
                defaultBlock(n);
            } else {
                disableBlock(n);
            }
        }

        void drawBlock(uint8_t n, uint16_t color, uint16_t background) {
            uint8_t x = ((n - 1) % COUNT_BLOCKS_IN_LINE);
            uint8_t y = (n - 1) / COUNT_BLOCKS_IN_LINE;
            
            display->fillRoundRect((x * 20) + 3, (y * 20) + dy + 5, 18, 18, 1, background);
            display->drawRect((x * 20) + 3, (y * 20) + dy + 5, 18, 18, color);
            display->setCursor((x * 20) + 3, (y * 20) + dy + 5 + 7);
            display->setTextColor(ST7735_WHITE);
            display->print(n);
        }

        void setActive(uint8_t n) {
             defaultBlock(active);
             active = n;
             block(active);
             lan->getConfig()->setChannel(active);
        }

    public:
        ChannelPage(Display *display, uint8_t dy): Page(display, dy) {}

        void configure(Container *container) {
            lan = container->getLan();
            active = lan->getConfig()->getChannel();
            selected = active;
        }

        void onClick(uint8_t btn) {
            if (btn == BTN_OK) {
                if (selected == active) {
                    return goBack();
                }

                if (lan->isChannelActive(selected)) {
                    setActive(selected);
                }
            }
            
            uint8_t previewNumber = selected;

            if (btn == BTN_RIGHT) {
                selected++;
            }

            if (btn == BTN_LEFT) {
                selected--;
            }

            if (btn == BTN_UP) {
                selected -= COUNT_BLOCKS_IN_LINE;
            }

            if (btn == BTN_DOWN) {
                selected += COUNT_BLOCKS_IN_LINE;
            }

            if (selected > COUNT_CHANELS) {
                selected = COUNT_CHANELS;
            } else if (selected < 1) {
                selected = 1;
            }

            if (btn == BTN_RIGHT || btn == BTN_LEFT || btn == BTN_UP || btn == BTN_DOWN) {
                drawSelect(selected, previewNumber);
            }
        }

        void render() {
            display->setCursor(0, 50);
            display->println(F("Start scan chanels..."));
            lan->startTest();
            clear();
            for(uint8_t n = 1; n < lan->getCountChanels(); n++) {
                block(n);
            }
            lan->stopTest();
        }
};