#include <nRF24L01.h>
#include <RF24.h>
#include "config.h"

#define NUM_CHANELS 128

class Lan {
  private:
    uint8_t values[NUM_CHANELS];
    RF24 *radio;
    const uint8_t num_reps = 100;
    LanConfig config;
  public:
    Lan(RF24 *radio): radio(radio) {
        config = LanConfig();
    }

    LanConfig* getConfig() {
        return &config;
    }


    void init() {
        config.init();
        radio->begin();
        radio->setAutoAck(false);
        radio->setChannel(config.getChannel());
        radio->startListening();
        radio->setDataRate(RF24_250KBPS);
        radio->printDetails();
    }

    void test() {
        startTest();
        for(uint8_t i = 0; i < NUM_CHANELS; i++) {
            printf("%x", getChannelStatus(i));
        }
    }

    uint8_t getChannelStatus(uint8_t c) {
        return min(0xf,values[c]&0xf);
    }

    void startTest() {
        memset(values, 0, sizeof(values));
        int rep_counter = num_reps;
        while (rep_counter--) {
            int i = NUM_CHANELS;
            while (i--) {
            radio->setChannel(i);
            radio->startListening();
            delayMicroseconds(128);
            radio->stopListening();
            if ( radio->testCarrier() )
                ++values[i];
            }
        }
    }

    void stopTest() {
        
    }

    void check() {
        if (radio->available()) {

        }
    }
};

