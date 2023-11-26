#pragma once

#include "../../../lib/raylib.h"

class Velocity {
    public:
        void Set(Vector3 vel) {
            velocity = vel;
        }

        void Change(float x, float y, float z) {
            velocity.x += x;
            velocity.y += y;
            velocity.z += z;
        }

        Vector3 Get() {
            return velocity;
        }

        

        Vector3 velocity;

    private:



    protected:

        const static double MAX_ACCELERATION = 9.81; // Meters a second
        


        //const static inline double GRAVITATIONAL_CONSTANT = 6.67408e-11; // m^3 kg^-1 s^-2

};