#pragma once

class Member {
    private:
        uint8_t number;
        uint8_t isRoot = 0;
        Package *lastPackage;

        uint16_t lastTime = 0;
        uint16_t countPakages = 0;
    public:
        Member(uint8_t number, uint8_t isRoot): number(number),isRoot(isRoot) {}
        Member(uint8_t number): number(number){}

        uint8_t getNumber() {
            return number;
        }

        uint16_t getCountPakages() {
            return countPakages;
        }

        void setLastPackage(Package *p) {
            lastTime = millis();
            countPakages++;

            lastPackage = p;
        }
};
