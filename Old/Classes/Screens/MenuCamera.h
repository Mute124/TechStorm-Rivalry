#pragma once
#include "../lib/raylib.h"
#include "../Gameobj.h"


class MenuCameraComponent 
{
    public:
        // Is this hidden? I dont know you tell me
        bool isHidden = true;
        static inline Camera2D camera; // The camera for you know, seeing. 

        // Todo : Implement this.
        void Hide() {

        }

        MenuCameraComponent() {
            camera.target = (Vector2){GetMonitorWidth(GetCurrentMonitor()) / 2.0f, GetMonitorHeight(GetCurrentMonitor()) / 2.0f};
        }
};