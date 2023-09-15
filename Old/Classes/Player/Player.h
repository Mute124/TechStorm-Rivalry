/*
    Todo :
        Split this class into two. one for the controller, and the other for the actual playermodel
*/
#pragma once
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "../lib/rcamera.h"
#include "../Monobehavior.h"

#include "../Gameobj.h"
#include "../Flashlight.h"
#include "../Block.h"
#include "CameraComp.h"

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

class Player : public GameObject, public CameraComp
{

public:
    // player camera

    Vector3 getPosition()
    {
        return this->m_position;
    }

    // main constructor
    Player(Vector3 StartingPos, int MaxHP, const Model model, int CameraMode)
        : m_position(StartingPos),
          m_max(MaxHP),
          model(model),
          cameraMode(CameraMode),
          Footstep_Grass(LoadSound("resources/audio/footsteps_player_grass_01.ogg")),
          id(RegisterObj(this)),
          CameraComp((CameraData){
              StartingPos,
              {0.0f, 2.0f, 0.0f},
              {0.0f, 1.0f, 0.0f},
              45.0f,
              CAMERA_PERSPECTIVE})
    {

        this->playerLookPointer = new Ray();

        IdentifySelf();
        playerlist.push_back(this);
    };

    /**
     * Checks for player movement and switches camera mode.
     *
     * @return void
     */
    void CheckInput()
    {
        while (!WindowShouldClose())
        {
        }
    }

    void onDestroy() const override
    {
        delete this;
    };

    void onUpdate() override
    {
        playerLookPointer = &playerlook;
        playerlook.position = this->GetPosition();
        playerlook.direction = this->getTarget();
        CheckForBlockPlacement(MouseButton::MOUSE_BUTTON_LEFT, playerlook);
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

    void PlayFootsteps()
    {
    }

    void Draw() override
    {
        if (cameraMode != CAMERA_FIRST_PERSON)
        {
            if (this->doDraw)
            {
                DrawModel(model, this->getPosition(), 0.2f, GREEN);
            }
        }
        else
        {
            // empty because it shouldnt draw anything
        }
    }

    static Ray *GetLook(int id)
    {
    }

    Ray *GetSelfLook()
    {
        return this->playerLookPointer;
    }

    Ray GetSelfLookPointerless()
    {
        return this->playerlook;
    }

    Vector3 GetPosition() override
    {
        return this->getPosition();
    }

    void SetPosition(Vector3 position)
    {

        this->m_position = position;
    }

    void SetCameraMode(int mode)
    {
        this->cameraMode = mode;
    }

    void setDrawCondition(bool val)
    {
        this->doDraw = val;
    }

    // do not fucking touch this
    virtual ~Player()
    {

        delete this;
    }

    int GetType() const override
    {
        return PLAYER; // returns the player obj type
    }

    Model model; // Player model
    int cameraMode;

    Ray playerlook;
    Ray *playerLookPointer = &playerlook;

    // Sound Loading
    Sound Footstep_Grass = LoadSound("resources/audio/footsteps_player_grass_01.ogg");

    bool doDraw = true;

    static inline Player *GetPlayer(int id)
    {

        return playerlist[id - 1];
    }

    static inline void SetPositionFromId(int id, Vector3 newPosition)
    {
        playerlist[id - 1]->SetPosition(newPosition);
    }

    int getInternalPlayerId() {
        return this->internalplayerid;
    }

    void setXRotation() {
        this->model.transform = MatrixRotateX(0.0001f * (float)Global::Time::GetGameTime());
    }

    static inline std::vector<Player *> playerlist;

private:
    void IdentifySelf()
    {
        this->internalplayerid = playerlist.size() + 1;
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
    Vector3 m_position;
    Mesh m_mesh;

    // Global::Transform transform;
    Vector3 velocity;
    BoundingBox Box = GetModelBoundingBox(this->model);

    unsigned const int m_max = PLAYER_HP; // Max HP player can have
    unsigned int m_current;               // current HP

    mutable int internalplayerid;
};