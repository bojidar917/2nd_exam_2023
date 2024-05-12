#pragma once

#include "Appliance.h"

enum AppliancesType
{
    Fridge,
    Heater,
    TV
};

class Room
{
public:
    Room();
    Room(const char* name, const int numberOfOutlets, const float maxPowerConsumption);
    Room(const Room& other);
    Room& operator=(const Room& other);
    ~Room();

    void operator+=(const Appliance& appliance);
    void operator+(const Appliance& appliancelhs);
    void operator-=(const char* serialNumber);
    void operator-(const Appliance& appliancelhs);
    Appliance* operator[](const char* serialNumber) const;

    void addNewAppliance(const Appliance& appliance);
    void removeAppliance(const char* serialNumber);

    void addNewForbiddenAppliance(const AppliancesType appliance);
    void removeForbiddenAppliances(const AppliancesType appliance);

    void turnOnAppliance(const char* serialNumber);

    float getCurrentPowerConsuption() const;
    void printRoomInfo() const;

private:
//private variables
    char* name;
    int numberOfOutlets;
    int currentPluggesOutlets;
    float maxPowerConsumption;

    Appliance** appliances;
    int numberOfAppliances;
    int capacityOfAppliances;

    AppliancesType* forbiddenAppliances;
    int countOfForbiddenAppliances;
    int capacityOfForbiddenAppliances;

    bool overMaxPowerConsumption;

//private functions
    void clear();
    void copy(const Room& other);

    void resizeAppliances();
    void resizeForbiddenAppliances();

    // float getTotalPowerConsumption() const;

    bool checkPowerConsumption() const;
    bool checkForAvailableOutlet() const;
    void overPowerConsumption();

};