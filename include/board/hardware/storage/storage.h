#pragma once

#include "mbed.h"
#include "eeprom.h"

#define EEPROM_ADDR 0x0 // I2c EEPROM address is 0x00

/**
 *  storage.write(1, 32);
 *  storage.write(2, 78);
 *  Storage *storage = container->getStorage();
 *  printf("read data 1: %i \n", storage->read(1));
 *  printf("read data 2: %i \n", storage->read(2));
 */ 
class Storage
{
private:
    EEPROM *eeprom;
    PinName sda;
    PinName scl;
public:
    Storage(PinName sda, PinName scl): sda(sda), scl(scl) {}

    void init()
    {
        eeprom = new EEPROM(sda, scl, 0x00, EEPROM::T24C256);
    }

    void write(int key, int8_t data)
    {
        int writeData[1] = {data};
        eeprom->write(key, writeData, 1);
    }

    int8_t read(int key)
    {
        int data = 0;
        eeprom->read(key, &data, 1);
        return data;
    }
};