#include "MenuCamera.h"

MenuCameraComponent::MenuCameraComponent() {
    this->camera.target = (Vector2){GetMonitorWidth(GetCurrentMonitor()) / 2, GetMonitorHeight(GetCurrentMonitor()) / 2};
}

void MenuCameraComponent::Hide() {
    this->isHidden = true;
}