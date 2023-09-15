#pragma once

#include "../Core/Game.hpp"

#include "MenuCamera.h"
#include "Menu.h"
#include "../../lib/Buttons/src/ButtonR.h" // Needed for buttons.
#include "../Core/Main.hpp"

// I dont think there needs to be an explanation.
class MainMenu : public Menu
{
public:
    MainMenu() {}

    ~MainMenu() {

    }
    
    void Draw() const override
    {}

    // destroys self
    void Destroy() {
        delete mmen_start;
    }



private:
    bool DeleteRequested = false;
    ButtonR *mmen_start; // Main start button
};