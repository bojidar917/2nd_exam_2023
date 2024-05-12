#pragma once

#include "Appliance.h"

class HeatingAppliance : public Appliance
{
public:
    HeatingAppliance(const char* brand, const char* model, const char* serailNumber, const float power);

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual float getPower() const override;
    virtual void print() override;

    virtual Appliance* clone() const override;\

private:
    float currentPower;
    void setPower(const float power) override;
    void checkCodition();
};
