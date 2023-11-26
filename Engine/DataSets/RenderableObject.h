#pragma once
#include "ClipPlanes.h"
#include "../../lib/raylib.h"

typedef struct RenderableObject
{
    
    Model *model;
    ObjectTransform transform;
    int clipPlane;
};
