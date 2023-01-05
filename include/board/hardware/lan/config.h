
#pragma once

// #include <EEPROM.h>

#include "board/hardware/storage/storage.h"

#define LAN_CONFIG_SAVE_CHANNEL_ADDRESS 1

class LanConfig {
    private:
        Storage *s;
    public:
        LanConfig(Storage *s): s(s) {}
        
        void init() {
            if (getChannel() == 255) {
                setChannel(1);
            }
        }

        void setChannel(uint8_t n) {
            s->write(LAN_CONFIG_SAVE_CHANNEL_ADDRESS, n);
        }

        uint8_t getChannel() {
            return s->read(LAN_CONFIG_SAVE_CHANNEL_ADDRESS);
        }
};