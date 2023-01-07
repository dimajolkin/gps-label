#pragma once

class HeaderModel
{
    private:
        Container *c;
    public:
        uint8_t power = 0;
        uint16_t memory = 1;
        uint8_t number = 0;

    HeaderModel(Container *c): c(c) {
        update();
    }

    void update() {
        // number = c->getMemberService()->getMy()->getNumber();
        number++;// = c->getGPS()->getCountSatellites();
        power = c->getServer()->getPowerLevel();
        memory = c->getServer()->getAvailableMemory();
    }
};
