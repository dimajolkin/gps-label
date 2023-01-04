#pragma once

#include "mbed.h"
using BattaryCalcFunction = Callback<uint8_t(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage)>;

/**
 * @see https://github.com/rlogiacco/BatterySense
 */ 
class Battery
{
    private:
        uint16_t refVoltage;
        uint16_t minVoltage;
        uint16_t maxVoltage;
        float dividerRatio;
        AnalogIn *sense;

    /**
     * Symmetric sigmoidal approximation
     * https://www.desmos.com/calculator/7m9lu26vpy
     *
     * c - c / (1 + k*x/v)^3
     */
    inline uint8_t sigmoidal(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage)
    {
        // slow
        // uint8_t result = 110 - (110 / (1 + pow(1.468 * (voltage - minVoltage)/(maxVoltage - minVoltage), 6)));

        // steep
        // uint8_t result = 102 - (102 / (1 + pow(1.621 * (voltage - minVoltage)/(maxVoltage - minVoltage), 8.1)));

        // normal
        uint8_t result = 105 - (105 / (1 + pow(1.724 * (voltage - minVoltage) / (maxVoltage - minVoltage), 5.5)));
        return result >= 100 ? 100 : result;
    }

    /**
     * Asymmetric sigmoidal approximation
     * https://www.desmos.com/calculator/oyhpsu8jnw
     *
     * c - c / [1 + (k*x/v)^4.5]^3
     */
    inline uint8_t asigmoidal(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage)
    {
        uint8_t result = 101 - (101 / pow(1 + pow(1.33 * (voltage - minVoltage) / (maxVoltage - minVoltage), 4.5), 3));
        return result >= 100 ? 100 : result;
    }

    /**
     * Linear mapping
     * https://www.desmos.com/calculator/sowyhttjta
     *
     * x * 100 / v
     */
    inline uint8_t linear(uint16_t voltage, uint16_t minVoltage, uint16_t maxVoltage)
    {
        return (unsigned long)(voltage - minVoltage) * 100 / (maxVoltage - minVoltage);
    }
    public:
    /**
		 * Creates an instance to monitor battery voltage and level.
		 * Initialization parameters depend on battery type and configuration.
		 *
		 * @param minVoltage is the voltage, expressed in millivolts, corresponding to an empty battery
		 * @param maxVoltage is the voltage, expressed in millivolts, corresponding to a full battery
		 * @param sensePin is the analog pin used for sensing the battery voltage
		 */
    Battery(uint16_t minVoltage, uint16_t maxVoltage, uint16_t refVoltage, uint16_t dividerRatio, PinName sensePin)
    {
        this->minVoltage = minVoltage;
        this->maxVoltage = maxVoltage;
        this->refVoltage = refVoltage;
        this->dividerRatio = dividerRatio;
        this->sense = new AnalogIn(sensePin, refVoltage);
    }

    /**
		 * Returns the current battery level as a number between 0 and 100, with 0 indicating an empty battery and 100 a
		 * full battery.
		 */
    uint8_t level()
    {
        return this->level(this->voltage());
    }

    uint8_t level(uint16_t voltage)
    {
        if (voltage <= minVoltage)
        {
            return 0;
        }
        else if (voltage >= maxVoltage)
        {
            return 100;
        }
        else
        {
            return linear(voltage, minVoltage, maxVoltage);
        }
    }

    /**
		 * Returns the current battery voltage in millivolts.
		 */
    uint16_t voltage()
    {
        uint16_t reading = sense->read_voltage() * dividerRatio;
        return reading;
    }
};