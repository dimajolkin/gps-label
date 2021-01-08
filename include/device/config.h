
#pragma once

#define MEMBER_NUMBER 10

class MemberConfig {
    public:
        void init() {
            if (getNumber() == 255) {
                setNumber(1);
            }
        }

        void setNumber(uint8_t n) {
            EEPROM.update(MEMBER_NUMBER, n);
        }

        uint8_t getNumber() {
            return EEPROM.read(MEMBER_NUMBER);
        }
};