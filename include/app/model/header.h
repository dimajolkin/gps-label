#pragma once

class HeaderModel
{
    private:
        ServiceLocator *c;
    public:
        uint8_t power = 10;
        uint16_t memory = 1;
        uint8_t number = 0;

    HeaderModel(ServiceLocator *c): c(c) {
        update();
    }

    void update() {
        // number = c->getMemberService()->getMy()->getNumber();
        number = c->getGPS()->getCountSatellites();
    }
};
