#pragma once
#include "Monobehavior.h"
#include "Gameobj.h"
#include "lib/raylib.h"

// since there will only be one skybox, this is all we need
class Skybox : public GameObject
{
public:
    Skybox() : ID(RegisterObj(this))
    {
        this->model.materials[0].shader = skybox_shader;

        tag.Tag = tag.Translate("Skybox") ;

 
    };
    ~Skybox(){};
    // TODO : implement lambda variables and functions


    void Draw() const override
    {
        // TODO : Implement this and make sure it works
        /*
            We need to implement this, we need to draw the skybox
            as such we need to enable backface culling in OpenGL because we are
            inside the cube that is the skybox
        */

    };
    int GetType() const override
    {
        return 0;
    };
    void onUpdate() const override
    {

        
    }

    void onCollision() const override{};

    BoundingBox GetBoundingBox() const override
    {
        return Global::BoxNull;
    };

    void onDestroy() const override{};

    Global::Tag tag; // dont modify this after initial creation and assignment
    Transform transform;
    Model model;
    BoundingBox Box = GetModelBoundingBox(model);
    const int ID;

private:
    Model genModel(float SizeFact)
    {
        return LoadModelFromMesh(GenMeshCube(SizeFact, SizeFact, SizeFact));
    }


    const 
};