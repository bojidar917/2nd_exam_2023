#include <cstring>
#include <iostream>

#include "Room.h"

Room::Room() : name(nullptr), numberOfOutlets(0), maxPowerConsumption(0), forbiddenAppliances(nullptr), appliances(nullptr)
{
    capacityOfAppliances = 0;
    numberOfAppliances = 0;

    countOfForbiddenAppliances = 0;
    capacityOfForbiddenAppliances = 0;

    overMaxPowerConsumption = false;
}

Room::Room(const char *name, const int numberOfOutlets, const float maxPowerConsumption) 
    : Room()
{
    if(numberOfOutlets >= 0)
        this->numberOfOutlets = numberOfOutlets;
    
    if(maxPowerConsumption >= 0)
        this->maxPowerConsumption = maxPowerConsumption;
    
    if(name)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    else
    {
        throw "could not create room with invalid name";
    }

}

Room::Room(const Room &other)
{
    copy(other);
}

Room &Room::operator=(const Room &other)
{
    if(this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

Room::~Room()
{
    clear();
}

void Room::operator+=(const Appliance &appliance)
{
    if(checkForAvailableOutlet())
    {
        addNewAppliance(appliance);
    }
}

void Room::operator+(const Appliance &appliancelhs)
{
    // what should we do here?
}

void Room::operator-=(const char* serialNumber)
{
    removeAppliance(serialNumber);
}

void Room::operator-(const Appliance &appliancelhs)
{
    // what should we do here?
}

Appliance* Room::operator[](const char *serialNumber) const
{
    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        if(strcmp(this->appliances[i]->getSerialNumber(), serialNumber) == 0)
        {
            return this->appliances[i];
        }
    }
    
    return nullptr;
}

void Room::addNewAppliance(const Appliance &appliance)
{
    if(overMaxPowerConsumption)
        std::cout << "you cannot add new appliances, this room is damaged by over power consumption";

    if(this->numberOfAppliances >= this->capacityOfAppliances)
        resizeAppliances();

    if(this->currentPluggesOutlets >= this->numberOfOutlets)
        std::cout << "not enough outles for more appliances";
    
    this->appliances[this->numberOfAppliances++] = appliance.clone();
    this->currentPluggesOutlets++;
}

void Room::removeAppliance(const char *serialNumber)
{
    int index = -1;
    for (int i = 0; i < numberOfAppliances; ++i)
    {
        if (strcmp(appliances[i]->getSerialNumber(), serialNumber) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < numberOfAppliances-1; ++i)
        {
            appliances[i] = appliances[i + 1];
        }
        this->numberOfAppliances--;
        delete appliances[numberOfAppliances];
        
        Appliance** temp = new Appliance*[this->capacityOfAppliances];
        for (int i = 0; i < this->numberOfAppliances; i++)
        {
            temp[i] = appliances[i];
        }
        if(temp)
        {
            delete[] this->appliances;
            this->appliances = temp;
        }
        this->currentPluggesOutlets--;
    }
}

void Room::addNewForbiddenAppliance(const AppliancesType appliance)
{

    for (int i = 0; i < this->countOfForbiddenAppliances; i++) //check if we already have the appliance in the list
    {
        if(this->forbiddenAppliances[i] == appliance)
            return;
    }
    
    if(this->countOfForbiddenAppliances >= this->capacityOfForbiddenAppliances)
        resizeForbiddenAppliances();
    
    this->forbiddenAppliances[this->countOfForbiddenAppliances++] = appliance;
}

void Room::removeForbiddenAppliances(const AppliancesType appliance)
{
    bool weHaveIt = false;
    for (int i = 0; i < this->countOfForbiddenAppliances; i++)
    {
        if(this->forbiddenAppliances[i] == appliance)
            weHaveIt = true;
    }

   if(weHaveIt)
   {
        for (int i = 0; i < this->countOfForbiddenAppliances-1; i++)
        {
            this->forbiddenAppliances[i] = this->forbiddenAppliances[i+1];
        }
        this->countOfForbiddenAppliances -= 1;
        AppliancesType *temp = new AppliancesType[this->capacityOfForbiddenAppliances];
        for (int i = 0; i < this->countOfForbiddenAppliances; i++)
        {
            temp[i] = this->forbiddenAppliances[i];
        }
        if(temp)
        {
            delete [] this->forbiddenAppliances;
            this->forbiddenAppliances = temp;
        }
   }
   else
    std::cout << "You don't have this type of appliance in the list" << std::endl;
}

void Room::turnOnAppliance(const char *serialNumber)
{
    for (int i = 0; i < numberOfAppliances; ++i)
    {
        if (strcmp(appliances[i]->getSerialNumber(), serialNumber) == 0)
        {
            appliances[i]->turnOn();
            return;
        }
    }

    std::cout << "Appliance with serial number " << serialNumber << " not found." << std::endl;

}

float Room::getCurrentPowerConsuption() const
{
    int currentPowerConsuption = 0;
    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        if(this->appliances[i]->isOn())
            currentPowerConsuption += this->appliances[i]->getPower();
    }
    
    return currentPowerConsuption;
}

void Room::printRoomInfo() const
{
    std::cout << "--- This is a/an " << this->name << " ---" << std::endl;

    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        std::cout << "Appliances: " << std::endl;
        appliances[i]->print();
        std::cout << std::endl;
    }

    for (int i = 0; i < this->countOfForbiddenAppliances; i++)
    {
        std::cout << "Forbidden Appliances: " << std::endl;
        std::cout << this->forbiddenAppliances[i];
        std::cout << std::endl;
    }
    
    std::cout << "Free outles: " << this->numberOfOutlets - this->currentPluggesOutlets << std::endl;
    std::cout << "Current power consumption" << this->getCurrentPowerConsuption();
}

void Room::clear()
{
    delete[] this->name;
    
    delete[] this->forbiddenAppliances;

    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        delete appliances[i];
    }
    delete [] this->appliances;
}

void Room::copy(const Room &other)
{
    //name
    if (other.name)
    {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
    else
    {
        this->name = nullptr;
    }

    //floats
    this->numberOfOutlets = other.numberOfOutlets;
    this->maxPowerConsumption = other.maxPowerConsumption;


    //forbiddenAppliances
    if (other.forbiddenAppliances)
    {
        this->countOfForbiddenAppliances = other.countOfForbiddenAppliances;
        int size = this->countOfForbiddenAppliances;
        this->forbiddenAppliances = new AppliancesType[size];
        for (int i = 0; i < size; ++i)
        {
            this->forbiddenAppliances[i] = other.forbiddenAppliances[i];
        }
    }
    else
    {
        this->forbiddenAppliances = nullptr;
    }

    //Appliances
    if (other.appliances)
    {
        this->numberOfAppliances = other.numberOfAppliances;
        this->countOfForbiddenAppliances = other.countOfForbiddenAppliances;
        int size = this->countOfForbiddenAppliances;
        
        this->appliances = new Appliance*[countOfForbiddenAppliances];

        for (int i = 0; i < size; ++i)
        {
            if (other.appliances[i])
            {
                this->appliances[i] = other.appliances[i]->clone();
            }
            else
            {
                this->appliances[i] = nullptr;
            }
        }
    }
    else
    {
        this->appliances = nullptr;
    }
}

void Room::resizeAppliances()
{
    // if (this->capacityOfAppliances == 0)
    //     this->capacityOfAppliances = 8;

    int newSize = this->capacityOfAppliances * 2 + 1;
    Appliance** newAppliances = new Appliance*[newSize];

    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        newAppliances[i] = appliances[i];
    }

    for (int i = 0; i < this->numberOfAppliances; i++)
    {
        delete appliances[i];
    }

    delete[] this->appliances;

    appliances = newAppliances;
    this->capacityOfAppliances = newSize;
}

void Room::resizeForbiddenAppliances()
{
    // if(this->capacityOfForbiddenAppliances == 0)
    //     this->capacityOfForbiddenAppliances = 4;

    int newSize = this->capacityOfForbiddenAppliances *2 + 1;
    AppliancesType* newAppliances = new AppliancesType[newSize];

    for (int i = 0; i < this->countOfForbiddenAppliances; i++)
    {
        newAppliances[i] = this->forbiddenAppliances[i];
    }

    if(newAppliances)
    {
        delete[] this->forbiddenAppliances;
        forbiddenAppliances = newAppliances;
        this->capacityOfForbiddenAppliances = newSize;
    }
}

// float Room::getTotalPowerConsumption() const
// {
//     float totalPowerConsumption = 0;
//     for (int i = 0; i < this->numberOfAppliances; i++)
//     {
//         totalPowerConsumption += this->appliances[i]->getPower();
//     }
    
//     return totalPowerConsumption;
// }

bool Room::checkPowerConsumption() const
{
    if(getCurrentPowerConsuption() >= this->maxPowerConsumption)
        return true;
    return false;
}

bool Room::checkForAvailableOutlet() const
{
    if(this->numberOfOutlets <= this->currentPluggesOutlets)
        return false;
    return true;
}

void Room::overPowerConsumption()
{
    clear();
    overMaxPowerConsumption = true;
}
