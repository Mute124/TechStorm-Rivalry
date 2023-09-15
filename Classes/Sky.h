#pragma once
#include "lib/raylib.h"
#include "lib/rlgl.h"
#include "lib/raymath.h"
#include "Gameobj.h"
#include "rlights.h"

class Sky : public GameObject
{
public:
    Sky()
    {
    }
    void Draw() const override
    {
    }
};

class SkyLightComponent 
{
public:

    class SkyLightComponentEx 
    {

    };
    SkyLightComponent() {}
    ~SkyLightComponent() {}
    /* data */

private:
    Light lights;

};

