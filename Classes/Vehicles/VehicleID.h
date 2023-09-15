#pragma once
#include "../Gameobj.h"

class VehicleID {
    protected:
        int id;
    public:
        VehicleID(Vehicle *vehicle) : id() {
            registerVehicle(vehicle);
        }

    private:
        void registerVehicle(Vehicle *vehicle)  {
            id = GameObject::RegisterObj(vehicle);
            delete vehicle;
        }
};