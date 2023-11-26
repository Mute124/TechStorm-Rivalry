#pragma once


struct Friction {
    public:
        Friction() {}


    // How much friction is there. 
    // NOTE: This affects the velocity of a object.
    double factor;

    // for later use.
    double potentialEnergy;
};