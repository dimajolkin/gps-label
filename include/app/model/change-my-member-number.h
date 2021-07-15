#pragma once

class ChangeMyMemberNumberModel
{
private:
    uint8_t number;

public:
    ChangeMyMemberNumberModel(uint8_t number): number(number) {}

    uint8_t getNumber()
    {
        return number;
    }

    void down()
    {
        number++;
        if (number > 10)
        {
            number = 1;
        }
    }

    void up()
    {
        number--;
        if (number < 1)
        {
            number = 1;
        }
    }
};