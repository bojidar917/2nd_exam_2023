#include <iostream>

#include "Fridge.h"

Fridge::Fridge(const char *brand, const char *model, const char *serailNumber, const float power)
    : Appliance(brand, model, serailNumber, power)
{
    setPower(power);
}

Appliance *Fridge::clone() const
{
    return new Fridge(*this);
}

float Fridge::getPower() const
{
    return this->power * numberOfCompressors;
}

void Fridge::print()
{
    std::cout << "---Fridge---" << std::endl;
    std::cout << this->model << std::endl;
    std::cout << this->brand << std::endl;
    std::cout << this->serialNumber << std::endl;
    std::cout << this->power << std::endl;
}
