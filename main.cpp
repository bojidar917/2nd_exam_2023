#include <iostream>

#include "Room.h"

#include "HeatingAppliance.h"
#include "Tv.h"
#include "Fridge.h"

void onlyAppliancesDemo()
{
    // HeatingAppliance heater("Gorenje", "k3", "SDF(*&)", 200);
    // TV tv("LG", "OLED", "sdk-100", 34, 1200);
    // Fridge fridge("TOSHIBA", "k3", "SDF(*&)", 100);

    // heater.turnOff();
    // heater.print();
 
    // fridge.print();

    // tv.print();

    // tv.turnOn();
    // tv.print();
}

int main()
{
    HeatingAppliance heater("Gorenje", "k3", "SDF(*&)", 200);

    Room bedroom("Bedroom1", 5, 2100);

    bedroom.addNewForbiddenAppliance(AppliancesType::Fridge);
    bedroom.addNewForbiddenAppliance(AppliancesType::TV);

    bedroom += heater;
    bedroom.turnOnAppliance("SDF(*&)");

    bedroom.printRoomInfo();

    return 0;
}