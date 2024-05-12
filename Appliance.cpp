#include <cstring>
#include <iostream>

#include "Appliance.h"

Appliance::Appliance() : brand(nullptr), model(nullptr), serialNumber(nullptr), power(0)
{
}

Appliance::Appliance(const char *brand, const char *model, const char *serialNumber, const float power) : Appliance()
{
    setBrand(brand);
    setModel(model);
    setSerailNumber(serialNumber);

    if(power > 0)
        this->power = power;
    else
        this->power = 0;

    turnedOn = false;
}

Appliance::Appliance(const Appliance &other)
{
    copy(other);
}

Appliance &Appliance::operator=(const Appliance &other)
{
    if(this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

Appliance::~Appliance()
{
    clear();
}

void Appliance::turnOn()
{
    this->turnedOn = true;
}

void Appliance::turnOff()
{
    this->turnedOn = false;
}

void Appliance::clear()
{
    delete [] this->brand;
    delete [] this->model;
    delete [] this->serialNumber;
}

void Appliance::copy(const Appliance &other)
{
    this->power = other.power;
    setBrand(other.brand);
    setModel(other.model);
    setSerailNumber(other.serialNumber);
    this->turnedOn = other.turnedOn;
}

void Appliance::setBrand(const char *brand)
{
    if (brand)
    {
        // I am not sure why this is a problem on the first call, but it was throwind
        // and error. Same wit the other 3. PLS HELP 😞

        // if (this->brand != nullptr)
        //     delete[] this->brand;

        size_t len = strlen(brand);
        this->brand = new(std::nothrow) char[len + 1];
        if (this->brand)
        {
            strcpy(this->brand, brand);
        }
        else
        {
            clear();
            throw std::bad_alloc();
        }
    }
}

void Appliance::setModel(const char *model)
{
    if (model)
    {
        // if (this->model)
        //     delete[] this->model;

        size_t len = strlen(model);
        this->model = new(std::nothrow) char[len + 1];
        if (this->model)
        {
            strcpy(this->model, model);
        }
        else
        {
            clear();
            throw std::bad_alloc();
        }
    }
}

void Appliance::setSerailNumber(const char *serialNumber)
{
    if (serialNumber)
    {
        // if (this->serialNumber)
        //     delete[] this->serialNumber;

        size_t len = strlen(serialNumber);
        this->serialNumber = new(std::nothrow) char[len + 1];
        if (this->serialNumber)
        {
            strcpy(this->serialNumber, serialNumber);
        }
        else
        {
            clear();
            throw std::bad_alloc();
        }
    }
}

void Appliance::setPower(const float power)
{
    this->power = power;
}
