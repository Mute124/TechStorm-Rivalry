#pragma once

#include "CameraData.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

class CameraComp
{
public:
    CameraComp(CameraData cameradata) : camera(cameradata.constructToCamera()) {

    }

    Vector3 getPosition()
    {
        return this->camera.position;
    }

    Vector3 getTarget()
    {
        return this->camera.target;
    }

    Vector3 getup()
    {
        return this->camera.up;
    }
    float getFOVY()
    {
        return this->camera.fovy;
    }

    float getProjection()
    {
        return this->camera.projection;
    }

    void setPosition(Vector3 value)
    {
        this->camera.position = value;
    }

    void setTarget(Vector3 value)
    {
        this->camera.target = value;
    }

    void setUp(Vector3 value)
    {
        this->camera.up = value;
    }

    void setFOVY(float value)
    {
        this->camera.fovy = value;
    }

    void setProjection(float value)
    {
        this->camera.projection = value;
    }

    Camera toCamera(CameraData data) {
        return data.constructToCamera();
    }

    Camera getSelfCamera() {
        return this->camera;
    }

    Camera *getSelfCameraPointer() {
        return &this->camera;
    }

    

private:

    Camera camera;
};