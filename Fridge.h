#pragma once

#include "Appliance.h"

class Fridge : public Appliance
{
public:
    Fridge(const char* brand, const char* model, const char* serailNumber, const float power);

    virtual float getPower() const override;
    virtual void print() override;

    virtual Appliance* clone() const override;

private:
    int numberOfCompressors;
};