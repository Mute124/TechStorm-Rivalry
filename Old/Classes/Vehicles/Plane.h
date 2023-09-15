#pragma once
#include "../lib/raylib.h"
#include "../Gameobj.h"
#include "../lib/rlgl.h"
#include <math.h>
#include "../lib/raymath.h"
#include "../lib/rcamera.h"

class Plane : public GameObject
{
public:
    bool driving = false;
    Plane(Shader shader, Vector3 position, Player *player) : id(RegisterObj(this)), shader(shader), position(position)
    {
        Logman::CustomLog(LOG_INFO, "Creating Plane", NULL);
        // Harvest player id
        this->vplayerid = player->getInternalPlayerId();

        planelook = Player::GetPlayer(vplayerid)->GetSelfLook();
        this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
        this->model.materials[0].shader = shader;

        
        Drive();
        Logman::CustomLog(LOG_INFO, "Plane Created", NULL);
    }

    void Draw() override
    {


        DrawModel(model, this->position, 0.02f, WHITE);

       

    }

    void onUpdate() override
    {

        Logman::CustomLog(LOG_DEBUG, TextFormat("Position: %f, %f, %f", this->position.x, this->position.y, this->position.z), NULL);
        this->planelook = Player::GetPlayer(vplayerid)->GetSelfLook();
        this->model.transform = MatrixLookAt(this->position, Player::GetPlayer(vplayerid)->getSelfCamera().target, Player::GetPlayer(vplayerid)->getPosition());

        DrivingUpdate();
    }

    int GetType() const override
    {
        return VEHICLE;
    }

    int GetId() const override
    {
        return this->id;
    }

    Vector3 GetPosition() override
    {
        return this->position;
    }

    BoundingBox GetBoundingBox() override
    {
        return this->Box;
    }

    void onCollision() override
    {
    }

    void onDestroy() const override
    {

        delete planelook;
        delete this;
    }

    void Drive()
    {

        this->driving = true;
        if (Player::GetPlayer(vplayerid)->doDraw)
        {
            Player::GetPlayer(vplayerid)->setDrawCondition(true);
        }

        Player::GetPlayer(vplayerid)->SetPosition(this->position);
        Player::GetPlayer(vplayerid)->SetCameraMode(CAMERA_THIRD_PERSON);
    }

    void DrivingUpdate()
    {
        Player::GetPlayer(vplayerid)->setXRotation();
        this->Seat = Vector3Add(this->position, (Vector3){0.0f, 2.0f, 0.0f});

        Player::GetPlayer(vplayerid)->SetPosition(this->Seat);

        if (IsKeyDown(KEY_D))
        {
            this->model.transform = MatrixRotateX(0.0001f * (float)Global::Time::GetGameTime());
        }
        if (IsKeyDown(KEY_A))
        {
            this->model.transform = MatrixRotateX(-0.0001f * (float)Global::Time::GetGameTime());
        }
        if (IsKeyDown(KEY_W))
        {
            this->model.transform = MatrixRotateY(0.0001f * (float)Global::Time::GetGameTime());
        }
        if (IsKeyDown(KEY_S))
        {
            this->model.transform = MatrixRotateY(-0.0001f * (float)Global::Time::GetGameTime());
        }
    }

private:
    void CheckDeleteKey(KeyboardKey key)
    {
        if (IsKeyDown(key))
        {
            DeleteMe = true;
        }
    }

    Ray *planelook = new Ray();

    bool DeleteMe = false;
    const int id;
    int vplayerid;

    Vector3 Target;

    Vector3 position;

    Vector3 Seat;
    unsigned int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;

    Shader shader;

    Model model = LoadModel("resources/models/gltf/Biplane/biplane.glb");

    // ModelAnimation *animation = LoadModelAnimations("resources/models/gltf/Biplane/biplane.glb", );

    Texture normalmap;
    BoundingBox Box = GetModelBoundingBox(model);
};