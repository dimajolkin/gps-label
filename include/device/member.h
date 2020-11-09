#pragma once

class Member {
    private:
        uint8_t number;
        uint8_t root = 1;
        Package *lastPackage;

        uint16_t lastTime = 0;
        uint16_t countPakages = 0;
    public:
        Member(uint8_t number, uint8_t root): number(number),root(root) {}
        Member(uint8_t number): number(number){}

        uint8_t getNumber() {
            return number;
        }

        uint8_t getPing() {
            return 1;
        }

        uint8_t isRoot() {
            return root;
        }

        uint16_t getCountPakages() {
            return countPakages;
        }

        void setLastPackage(Package *p) {
            lastTime = millis();
            countPakages++;

            lastPackage = p;
        }

        void update() {
            
        }
};
