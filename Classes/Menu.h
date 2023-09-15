#pragma once
#include "lib/raylib.h"

// used for all menu objects.
class Menu {
    public: 
        virtual void Draw() const = 0;
        virtual ~Menu() {}
    
    private:
        Vector2 size; // X is the width, Y is the height.

};