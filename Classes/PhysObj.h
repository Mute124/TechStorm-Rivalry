/*
    There is a problem that needs to be solved, we need to have this class be flexible and not require any editing on the childs part,
    this should just manage
    since this will need to be able to modify the child, we need to use CRTP (Curiously Recurring Template Pattern)
*/
#pragma once
#include "Globals.h"


class PhysObj {
    private:
        Vector3 m_Velocity;
        double m_Acceleration;
        
    public:

        // simulate the next frame
        void Update() {};

        


};
