#pragma once
#include "../lib/raylib.h"
#include "../../../Engine/Classes/GameObject/Gameobject.h"
#include "../lib/rlgl.h"
#include <math.h>
#include "../lib/raymath.h"
#include "../lib/rcamera.h"
#include "../../../Engine/Classes/Player/Player.h"

class Plane : public GameObject
{
public:
    bool driving = true;

    Plane(Shader shader, Vector3 position) : id(RegisterObj(this)), shader(shader), position(position)
    {
        Logman::CustomLog(LOG_INFO, "Creating Plane", NULL);

        this->model.materials[0].shader = shader;

        this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

        Logman::CustomLog(LOG_INFO, "Plane Created", NULL);
    }

    int GetType() const override {
        return NULL;
    }

    int GetId() const override {
        return id;
    }

    BoundingBox GetBoundingBox() override {

        return this->Box;
    }


    void onDestroy() const override {
        delete this;
    }


    void Draw() override
    {

        if (driving) {
            //model.transform = MatrixLookAt((Vector3){position.x, position.y + 2.0f, position.z}, Player::cameraComponent->getTarget(), (Vector3){0.0f, 1.0f, 0.0f});
            //DrawModel(model, (Vector3){Player::cameraComponent->getPosition().x, Player::cameraComponent->getPosition().y -2.0f, Player::cameraComponent->getPosition().z}, 0.02f, WHITE);
        } else {
            DrawModel(model, this->position, 0.02f, WHITE);
        }
        

       

    }

    ~Plane() {
        delete this;
    }

private:
    

    Shader shader;

    Vector3 position;
    Model model = LoadModel("resources/models/gltf/Biplane/biplane.glb");

    // ModelAnimation *animation = LoadModelAnimations("resources/models/gltf/Biplane/biplane.glb", );
   
    const int id;
    Texture normalmap;
    BoundingBox Box = GetModelBoundingBox(model);
};