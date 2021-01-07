#pragma once

#include <nRF24L01.h>
#include <RF24.h>
#include "package.h"
#include "config.h"

class Lan {
  private:
    static const uint8_t num_channels = 128;
    static const int num_reps = 100;
    uint8_t values[128];
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
        const byte address[6] = "00001";

        config.init();
        radio->begin(); //активировать модуль

        radio->setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
        radio->setRetries(0, 15);     //(время между попыткой достучаться, число попыток)
        radio->setPayloadSize(32);     //размер пакета, в байтах
        radio->openReadingPipe(1, address);      //хотим слушать трубу 0
        radio->setChannel(40);  //выбираем канал (в котором нет шумов!)
        radio->setPALevel(RF24_PA_HIGH); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
        radio->setDataRate(RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
        //должна быть одинакова на приёмнике и передатчике!
        //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
        radio->printDetails();
        delay(5000);
        radio->powerUp(); //начать работу
        radio->startListening();  //начинаем слушать эфир, мы приёмный модуль
    }

    bool available() {
        return radio->available();
    }

    void send(Package *package) {
        radio->write(package, sizeof(Package));
    }

    Package read() {
        Package package;
        radio->read(&package, sizeof(package));
        return package;
    }

    uint8_t isChannelActive(uint8_t c) {
        return min(0xf, values[c]&0xf) == 0;
    }

    void startTest() {
        radio->stopListening();
         
        memset(values,0,sizeof(values));
        int rep_counter = num_reps;
        while (rep_counter--) {
            int i = num_channels;
            while (i--) {
                radio->setChannel(i);
                radio->startListening();
                delayMicroseconds(128);
                radio->stopListening();
                if (radio->testCarrier()) {
                    ++values[i];
                }
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
};

