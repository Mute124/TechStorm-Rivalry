#pragma once
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "../Gameobj.h"
#include "VehicleID.h"
#include "VehicleTypes.h"



class Vehicle : public GameObject, public VehicleID {
    public:
        Vehicle(const Vtypes VehicleType) :  vtype(VehicleType), VehicleID(this) {}


        
        virtual void onDrive() {

        }

        virtual void onDriveUpdate() {

        }

        int GetType() const override {
            return 3; // Vehicle
        }
        
        bool isMobile;
        const char *tag;
        const Vtypes vtype;
        
    private:
        
        

};