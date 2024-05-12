#pragma once

class Appliance
{
public:
    Appliance();
    Appliance(const char* brand, const char* model, const char* serailNumber, const float power);
    Appliance(const Appliance& other);
    Appliance& operator=(const Appliance& other);
    virtual ~Appliance();

    virtual Appliance* clone() const = 0;

    virtual void turnOn();
    virtual void turnOff();
    virtual void print() = 0;

    bool isOn() const {return turnedOn;}

    virtual float getPower() const = 0;

    const char* getSerialNumber() const {return serialNumber;}

protected:
    void setBrand(const char* brand);
    void setModel(const char* model);
    void setSerailNumber(const char* serailNumber);

    virtual void setPower(const float power);

protected:
    char* brand;
    char* model;
    char* serialNumber;
    float power;
    bool turnedOn;

    void clear();
    void copy(const Appliance& other);

};