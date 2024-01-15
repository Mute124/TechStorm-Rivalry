#include "MenuCamera.h"

MenuCamera::MenuCamera() {

    camera = Camera2D{0};
    
                Vector2 a{
                (float)GetMonitorWidth(GetCurrentMonitor()) / 2.0f,
                (float)GetMonitorHeight(GetCurrentMonitor()) / 2.0f
                };

                camera.target = a;
}