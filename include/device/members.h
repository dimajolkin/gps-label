#pragma once

#include "device/member.h"

class MemberCollection {
    private:
        static const uint8_t MAX_SIZE = 6;
        Member *list[MAX_SIZE] = {0, 0, 0, 0, 0, 0};
    public:
        MemberCollection() {}

        uint8_t getSize() {
            return MAX_SIZE;
        }

        void append(Member *m) {
            list[m->getNumber()] = m;
        }

        void remove(Member *m) {
            delete list[m->getNumber()];
            list[m->getNumber()] = 0;
        }

        uint8_t has(uint8_t number) {
            return list[number] != 0;
        }

        Member* get(uint8_t number) {
            return list[number];
        }

        void registerPakage(Package *pack) {
            if (!has(pack->n)) {
                append(new Member(pack->n));
            } else {
                get(pack->n)->setLastPackage(pack);
            }
        }
};