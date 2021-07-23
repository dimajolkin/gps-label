#pragma once

class Member {
    private:
        uint8_t number;
        uint8_t isMyDevice = 0;
        Package *lastPackage;

        uint16_t lastTime = 0;
        uint16_t countPakages = 0;
        uint16_t ping = 0;
    public:
        Member(uint8_t number, uint8_t isMyDevice): number(number),isMyDevice(isMyDevice) {}
        Member(uint8_t number): number(number) {}

        uint8_t getNumber() {
            return number;
        }

        void setNumber(uint8_t n) {
            number = n;
        }

        uint8_t getPing() {
            return ping;
        }

        uint8_t isMy() {
            return isMyDevice;
        }

        uint16_t getCountPakages() {
            return countPakages;
        }

        void setLastPackage(Package *p) {
            lastPackage = p;
            lastTime = millis();
            countPakages++;           
        }

        void update() {
             if (lastTime) {
                ping = (lastTime - millis()) / 1000;
            }
        }
};
