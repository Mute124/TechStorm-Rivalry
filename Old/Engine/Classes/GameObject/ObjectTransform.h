#pragma once
#include "../../../lib/raylib.h"
#include "../../../lib/raymath.h"

#include "../../DataSets/Euler.h"

class Rotation
{

public:
    void TransformRotate(float w, float x, float y, float z)
    {
        rotation.w += w;
        rotation.x += x;
        rotation.y += y;
        rotation.z += z;
    }

    Quaternion rotation;
};

// Size
class Scale
{
    Vector3 size;
};

class Position
{
public:
    // add to position values
    void Translate(float x, float y, float z)
    {
        position.x += x;
        position.y += y;
        position.z += z;
    }

    void Set(Vector3 position)
    {
        this->position = position;
    }

    Vector3 position;
};

class ObjectTransform
{
public:
    Rotation rotation;
    Scale scale;
    Position position;
};