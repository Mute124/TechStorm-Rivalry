#pragma once
#include "../../../common.h"


class CameraData
{
public:
    Vector3 position; // Camera position
    Vector3 target;   // Camera target it looks-at
    Vector3 up;       // Camera up vector (rotation over its axis)
    float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

    Camera constructToCamera() {
        Camera camera = {
            position,
            target,
            up,
            fovy,
            projection
        };
        return camera;
    }
};