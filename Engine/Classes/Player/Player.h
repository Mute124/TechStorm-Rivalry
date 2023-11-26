/*
    Todo :
        Split this class into two. one for the controller, and the other for the actual playermodel
*/
#pragma once
#include "../../../lib/raylib.h"
#include "../../../lib/raymath.h"
#include "../../../lib/rcamera.h"
#include "../../DataSets/Globals.h"

#include "../GameObject/Gameobject.h"
#include "../../../Minero/Classes/Flashlight/Flashlight.h"
#include "../ShapeBase/Block/Block.h"
#include "CameraComp.h"
#include "PlayerHealthComp.h"

#include <thread>
#include <stdio.h>
#include <stdlib.h>

#define PLAYER_HP 100 


typedef enum
{
    Action_Idle = 0,
    Action_Walk,
    Action_Break,
    Action_Fly,
    Action_Place
} Player_Action;
class Player : public GameObject
{

public:

    class BuildingComp {
        public:

            static void SetGlobalVariables(Color buildcolor) {
                buildColor = buildcolor;
            }

            void cast(Vector3 castPosition, bool isGroundLocked);

        private:

            static inline Color buildColor;
    };

    // main constructor
    Player(Vector3 StartingPos, int MaxHP, const Model model, int CameraMode)
        : position(StartingPos),
          m_max(MaxHP),
          model(model),
          cameraMode(CameraMode),

          id(RegisterObj(this)),
          cameraComponent(new CameraComp((CameraData){
              StartingPos,
              {0.0f, 2.0f, 0.0f},
              {0.0f, 1.0f, 0.0f},
              45.0f,
              CAMERA_PERSPECTIVE}))
    {

    };

    void onDestroy() const override
    {
        delete this;
    };

    void onUpdate() override
    {

        if (cameraMode != CAMERA_FIRST_PERSON) {
            if (this->doDraw) {
                DrawModel(model, this->cameraComponent->getPosition(), 0.2f, GREEN);
            }
        }
    };

    void onCollision() override{};

    int GetId() const override
    {
        return this->id;
    }

    BoundingBox GetBoundingBox() override
    {
        return this->Box;
    };

    // sends player data to the games render
    void Draw() override
    {
        if (cameraMode != CAMERA_FIRST_PERSON)
        {
            if (this->doDraw)
            {
                DrawModel(model, this->cameraComponent->getPosition(), 0.2f, GREEN);
            }
        }
        else
        {
            // empty because it shouldnt draw anything
        }

        
    }


    // do not fucking touch this
    virtual ~Player()
    {
        delete cameraComponent;
        delete this;
    }

    int GetType() const override
    {
        return PLAYER; // returns the player obj type
    }

    Model model; // Player model
    int cameraMode;

    bool doDraw = true;


    CameraComp *cameraComponent;

    bool isRunning;
private:


    void CalculateMovement() {
        position = Vector3Add(position, velocity);

        
        
    }

    const int id;
    static void CheckForBlockPlacement(MouseButton Trigger, Ray ray)
    {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            std::vector<GameObject *> objects = RequestObjectList();
            // Loop through all the objects and check for a collision, then poof!
            for (auto &obj : objects)
            {
                if (obj->GetType() == BLOCK)
                {
                    Block *block = static_cast<Block *>(obj);

                    // Check for a collision between the mouse ray and the block's
                    // bounding box
                    if (Global::Math::CheckCollisionRayBox(ray, block->GetBounds(), NULL))
                    {
                        // Remove the block from the vector and free its memory
                        std::vector<GameObject *>::iterator it =
                            std::find(objects.begin(), objects.end(), obj);
                        if (it != objects.end())
                        {
                            objects.erase(it);
                        }
                        break;
                    }
                }
            }
        }
    }

    // CameraComp cameraComponent;
    RayCollision collision = {0};

    // KeyboardKey *CurrentKeyDown;
    Vector3 position;
    Mesh mesh;

    // Global::ObjectTransform transform;
    Vector3 velocity;
    BoundingBox Box = GetModelBoundingBox(this->model);

    int m_max = PLAYER_HP;
};