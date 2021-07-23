#pragma once

class HeaderModel
{
public:
    uint8_t power = 10;
    uint16_t memory = 1;
    uint8_t number = 0;

    HeaderModel(ServiceLocator *c) {
        update(c);
    }

    void update(ServiceLocator *c) {
        number = c->getMemberService()->getMy()->getNumber();
    }
};
