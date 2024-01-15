#pragma once
#include "Gameobject.h"
#include "../Project/Game/Game.h"

typedef struct
{
    MaterialMap albedo;
    MaterialMap normal;
    MaterialMap emissive;
    MaterialMap metallic;
    MaterialMap roughness;
    MaterialMap ao;

    MaterialMap MRAO;
} MaterialMapList;

class Object : public GameObject
{
public:
    Object(Model model, MaterialMapList materialMapList)
    {


    };

    void Destroy()
    {
        this->~Object();
    }

    void onUpdate() override
    {
    }

    void Draw() override
    {
    }

    Vector3 position;
    float scale;
    Model model;

    MaterialMapList materialMapList;
};
