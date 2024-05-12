#include <iostream>

#include "HeatingAppliance.h"

HeatingAppliance::HeatingAppliance(const char *brand, const char *model, const char *serailNumber, const float power)
: Appliance(brand, model, serailNumber, power)
{
    this->turnedOn = false;
    checkCodition();
}

Appliance *HeatingAppliance::clone() const
{
    return new HeatingAppliance(*this);
}

void HeatingAppliance::setPower(const float power)
{
    if(power >= 0)
        this->power = power;
}

void HeatingAppliance::turnOn()
{
    this->turnedOn = true;
    checkCodition();
}

void HeatingAppliance::turnOff()
{
    this->turnedOn = true;
    setPower(0);
}

float HeatingAppliance::getPower() const
{
    return this->currentPower;
}

void HeatingAppliance::print()
{
    std::cout << "---Heating Appliance---" << std::endl;
    std::cout << this->model << std::endl;
    std::cout << this->brand << std::endl;
    std::cout << this->serialNumber << std::endl;
    std::cout << this->currentPower << std::endl;
}

void HeatingAppliance::checkCodition()
{
    if(this->turnedOn)
        this->currentPower = this->power;
    else
        this->currentPower = 0;
}
