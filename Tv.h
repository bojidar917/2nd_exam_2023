#pragma once

#include "Appliance.h"

class TV : public Appliance
{
public:
    TV(const char* brand, const char* model, const char* serailNumber, const float power, const int brightness);

    virtual float getPower() const override;

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual void print() override;

    virtual Appliance* clone() const override;

private:
    int brightneess;
    float currentPower;
    
    void setPower(const float power) override;
    void checkCodition();
};