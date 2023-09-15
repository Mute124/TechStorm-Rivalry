#include "Gizmo.hpp"

Gizmo::Gizmo() {

}

void Gizmo::EnableGizmo()
{
    this->shouldDrawGizmo = true;
    Logman::CustomLog(LOG_INFO, "Enabling Light Gizmo Drawing", NULL);
}

void Gizmo::DisableGizmo()
{
    this->shouldDrawGizmo = false;
    Logman::CustomLog(LOG_INFO, "Disabling Light Gizmo Drawing", NULL);
}
