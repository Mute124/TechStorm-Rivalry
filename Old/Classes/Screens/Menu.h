#pragma once
#include "../lib/raylib.h"
#include "MenuCamera.h"

// used for all menu objects.
class Menu
{
public:
    virtual void Draw() const = 0;

    
    virtual ~Menu() {
        delete this;
    }

    Menu() {
        menuCamera = new MenuCameraComponent();
    }
   
    MenuCameraComponent *menuCamera;

    private :

        Vector2 size; // X is the width, Y is the height.
};