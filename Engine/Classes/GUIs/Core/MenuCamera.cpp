#include "MenuCamera.h"

MenuCamera::MenuCamera() {
    this->camera.target = (Vector2){GetMonitorWidth(GetCurrentMonitor()) / 2, GetMonitorHeight(GetCurrentMonitor()) / 2};
}