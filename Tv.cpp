#include <iostream>

#include "Tv.h"

TV::TV(const char *brand, const char *model, const char *serailNumber, const float power, const int brightness)
    : Appliance(brand, model, serailNumber, power)
{
    if(brightness > 0)
        this->brightneess = brightness;

    this->turnedOn = false;
    checkCodition();
}

Appliance *TV::clone() const
{
    return new TV(*this);
}

float TV::getPower() const
{
    return this->currentPower;
}

void TV::turnOn()
{
    this->turnedOn = true;
    checkCodition();
}

void TV::turnOff()
{
    this->turnedOn = false;
    checkCodition();
}

void TV::print()
{
    std::cout << "---TV Appliance---" << std::endl;
    std::cout << this->model << std::endl;
    std::cout << this->brand << std::endl;
    std::cout << this->serialNumber << std::endl;
    std::cout << this->currentPower << std::endl;
}

void TV::setPower(const float power)
{
    this->power = power;
}

void TV::checkCodition()
{
    if(this->turnedOn)
    {
        this->currentPower = brightneess/100 * this->power;
    }
    else
    {
        this->currentPower = 0.05;
    }
}
