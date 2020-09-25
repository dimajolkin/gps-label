#include <nRF24L01.h>
#include <RF24.h>
#include "package.h"
#include "config.h"

class Lan {
  private:
    const uint8_t num_channels = 128;
    uint8_t values[128];
    const int num_reps = 100;
    RF24 *radio;
    LanConfig config;
  public:
    Lan(RF24 *radio): radio(radio) {
        config = LanConfig();
    }

    uint8_t getCountChanels() {
        return num_channels;
    }

    LanConfig* getConfig() {
        return &config;
    }

    void init() {
        config.init();
        radio->begin();
        radio->setAutoAck(false);
        radio->startListening();
        delay(5000);
        radio->stopListening();
    }

    uint8_t available() {
        return radio->available();
    }

    void send(Package *package) {
        radio->write(package, sizeof(Package));
    }

    Package* read() {
        Package *package;
        radio->read( &package, sizeof(Package) );
        return package;
    }

    uint8_t isChannelActive(uint8_t c) {
        return min(0xf,values[c]&0xf) == 0;
    }

    void startTest() {
            memset(values,0,sizeof(values));
            int rep_counter = num_reps;
            while (rep_counter--) {
                int i = num_channels;
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

    void test() {
            startTest();
            for (uint8_t i = 0; i < 128; i++) {
                printf("%x", isChannelActive(i));
            }
            printf("\n\r");
    }

    void stopTest() {
        
    }

    void check() {
        if (radio->available()) {

        }
    }
};

