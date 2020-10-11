
#pragma once

class Server {

    public:
        uint8_t getPowerPercent() {
            return 10;
        }

        int16_t getAvailableMemory() {
            return availableMemory(0, 4096);
        }
};