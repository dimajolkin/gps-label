
#pragma once

class Server {
    private:
        uint8_t power = 10;
        uint16_t memory = 0;

        int16_t availableMemory(uint16_t min, uint16_t max) {
            if (min == max-1) {
                return min;
            }
                

            int16_t size=max;
            int16_t lastSize=size;
            byte *buf;
            while ((buf = (byte *) malloc(size)) == NULL)
            {
                lastSize=size;
                size-=(max-min)/2;
            };

            free(buf);
             return availableMemory(size,lastSize);
        }

    public:
        uint8_t getPowerPercent() {
            return power;
        }

        int16_t getAvailableMemory() {
            return memory;
        }

        void update() {
            memory = availableMemory(0, 4096);
            power = 10;
        }
};