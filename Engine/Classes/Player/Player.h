/*
    Todo :
        Split this class into two. one for the controller, and the other for the actual playermodel
*/
#pragma once
#include "../../../lib/raylib.h" // PLEASE FOR THE LOVE OF GOD DONT PUT. A. FUCKING. SPACE. YOU. MONKEY!
#include "../../../lib/raymath.h"
#include "../../../lib/rcamera.h"
#include "../../DataSets/Globals.h"

#include "../GameObject/Gameobject.h"
#include "../../../Minero/Classes/Flashlight/Flashlight.h"
#include "../ShapeBase/Block/Block.h"
#include "CameraComp.h"
#include "PlayerHealthComp.h"
#include "PlayerController.h"

#include "../../../Minero/Classes/Item/Item.h"

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

    class Crosshair {
        public:
            Crosshair(int width, int height, Color color) : width(width), height(height), color(color) {
                position = {(float)width / 2, (float)height / 2};
            }

            void Draw() {
                

            }

        int width, height;
        Color color;

        Vector2 position;
    };

    class Hand : public GameObject {

        public:


            Vector3 offset;
            Vector3 position;


            Item item;
            Hand(Model model) : offset({0.0f, 0.0f, 0.0f}) {

            }

            void onUpdate() override {
                
            }

            void onDestroy() const override {
                
            }

            int GetId() const override{
                return 0;
            }

            int GetType() const override{
                return 0;
            }

            void Draw() override {
                //DrawModel(model, this->position, 0.05f, GREEN);
            }


            
            
    };

    // main constructor
    Player(Vector3 StartingPos, int MaxHP, const Model model, int CameraMode)
        : position(StartingPos),
          m_max(MaxHP),
          model(model),
          cameraMode(CameraMode),

          id(RegisterObj(this))
       
    {
       cameraComponent = new CameraComp(CameraData{
              {0.0f, 0.0f, 4.0f},
              {0.0f, 2.0f, 0.0f},
              {0.0f, 2.0f, 0.0f},
              45.0f,
              CAMERA_PERSPECTIVE});

        hand = new Hand(model);
        crosshair = new Crosshair(GetScreenWidth(), GetScreenHeight(), BLACK);

        healthComp = new PlayerHealthComp(m_max);

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

        if (controller->canMove) {
            controller->Update(cameraComponent->getSelfCameraPointer());
        }

        if (IsKeyDown(KEY_F)) {
            startDriving = true;
        }
    
        if (IsKeyDown(KEY_V)) {
            startDriving = false;
        }
        
        if (startDriving) {
            Drive();
        }
        
        
        
        hand->position = Vector3Add(this->cameraComponent->getPosition(), GetCameraForward(this->cameraComponent->getSelfCameraPointer()));//= Vector3Normalize(Vector3Add(Vector3Divide(this->cameraComponent->getTarget(), {2.0f, 2.0f, 2.0f}), GetCameraForward(this->cameraComponent->getSelfCameraPointer())));
        //hand->model.transform = MatrixLookAt(this->cameraComponent->getPosition(), this->cameraComponent->getTarget(), {0.0f, 1.0f, 0.0f});
        //hand->model = model;
    };

    void onCollision() override {};

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

        hand->Draw();

        
    }

    void Drive() {
        CameraMoveForward(cameraComponent->getSelfCameraPointer(), 0.01f, false);
    }



    // do not fucking touch this
    virtual ~Player()
    {
        delete cameraComponent;
        delete controller;
        delete hand;
        delete this;
    }

    int GetType() const override
    {
        return PLAYER; // returns the player obj type
    }

    Model model; // Player model
    int cameraMode;

    bool doDraw = true;


    static void Setup() {

    }
    static inline CameraComp *cameraComponent;

    PlayerController *controller = new PlayerController(KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE, KEY_C, cameraMode);
    

    bool isRunning;

    static inline Hand *hand;
    Crosshair *crosshair;
    PlayerHealthComp *healthComp;

private:

    bool startDriving = false;
    const int id;
    static void CheckForBlockPlacement(MouseButton Trigger, Ray ray)
    {
/*  
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
        }*/
        
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