#pragma once
#include "common.h"
class MenuCamera
{
public:
    bool m_isHidden = true;
    Camera2D camera;

    MenuCamera() {


        camera.target = Vector2{ (float)GetMonitorWidth(GetCurrentMonitor()) / 2.0f, (float)GetMonitorHeight(GetCurrentMonitor()) / 2.0f };
    }
};