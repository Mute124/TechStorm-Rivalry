#pragma once
#include "lib/raylib.h"
#include "Gameobj.h"

class MenuCamera 
{
    public:
        bool m_isHidden = true;
        Camera2D camera;

        MenuCamera() {
            camera.target = (Vector2){GetMonitorWidth(GetCurrentMonitor()) / 2.0f, GetMonitorHeight(GetCurrentMonitor()) / 2.0f};
        }
};