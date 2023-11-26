#pragma once
#include "../../lib/raylib.h"

class Euler {
    public:

        Vector3 ToVec3() {
            return (Vector3){Yaw, Pitch, Roll};
        }
        
    float Yaw;
    float Pitch;
    float Roll;
};