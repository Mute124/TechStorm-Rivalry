#pragma once
#include "common.h"
#include "Globals.h"
#include "Gameobject.h"
#include "Block.h"
#include "Item.h"


#define STARTINGHP 100 
class PlayerController
{

private:

    int mode;

    float speed;
    float tiltSpeed;
    const float maxTiltRight = 10.0f; // Positive
    const float maxTiltLeft = -10.0f; // Negative
    float crouchSpeed;


    float screenTilt;

    float mouseSensitivity = 0.05f;

    KeyboardKey forward, backward, left, right, jump, crouch, tiltLeft, tiltRight;

    // needs to be optimized, technically we dont need parameters, we can just use this classes variable for it.
    float CalculateCameraTilt() {

        static const float NOCHANGE= 0.0f;

        return NOCHANGE;
    
    }
public:

    bool isRunning = false;
    bool canMove = true;
    bool isGrounded = false;

    PlayerController(KeyboardKey Forward, KeyboardKey Backward, KeyboardKey Left, KeyboardKey Right, KeyboardKey Jump, KeyboardKey Crouch, int mode) : forward(Forward), backward(Backward), left(Left), right(Right), jump(Jump), crouch(Crouch), mode(mode)
    {
#ifndef tiltLeft
        tiltLeft = KEY_Q;
#endif // !tiltLeft
#ifndef tiltRight
        tiltRight = KEY_E;
#endif // !tiltRight


    }

    void SetSpeed(float speed) {
        this->speed = speed;
    }

    void Update(Camera* camera)
    {

        // Camera PRO usage example (EXPERIMENTAL)
        // This new camera function allows custom movement/rotation values to be directly provided
        // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
        UpdateCameraPro(camera,
            Vector3{
                (IsKeyDown(forward) || IsKeyDown(KEY_UP)) * speed -      // Move forward-backward
                (IsKeyDown(backward) || IsKeyDown(KEY_DOWN)) * speed,
                (IsKeyDown(right) || IsKeyDown(KEY_RIGHT)) * speed -   // Move right-left
                (IsKeyDown(left) || IsKeyDown(KEY_LEFT)) * speed,
                (IsKeyDown(jump)) * speed -                                                 // Move up-down
                (IsKeyDown(crouch)) * speed
            },
            Vector3{
                GetMouseDelta().x * mouseSensitivity,                            // Rotation: yaw
                GetMouseDelta().y * mouseSensitivity,                            // Rotation: pitch
                CalculateCameraTilt()                // Rotation: roll
            },

            GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)

        
    }



};
class HealthBar
{
public:
    float CalculatePercentage(float hp, float max_hp)
    {
        float percentage = (float)hp / (float)max_hp;
        return percentage;
    }

    void Draw(Vector2 position)
    {
        float percentage = CalculatePercentage(hp, maxHP);

        DrawRectangle((int)position.x, (int)position.y, 100, 20, BLACK);
        DrawRectangleLines((int)position.x, (int)position.y, 100, 20, RED);
        DrawRectangle((int)position.x, (int)position.y, 100 * percentage, 20, GREEN);
    };

    float hp;
    float maxHP;
};
class PlayerHealthComp
{

public:
    HealthBar* healthBar;

    PlayerHealthComp(int maxHP)
    {
        healthBar = new HealthBar();

        healthBar->hp = 100;
        healthBar->maxHP = maxHP;
    }

    ~PlayerHealthComp() {
        delete this;
    }

    void DamagePlayer(float damage)
    {
        healthBar->hp -= damage;
    }

    void HealPlayer(int heal)
    {
        healthBar->hp += heal;
    }

    int GetMaxHealth()
    {
        return healthBar->maxHP;
    }

    int GetHealth()
    {
        return healthBar->hp;
    }
};
class CameraData
{
public:
    Vector3 position; // Camera position
    Vector3 target;   // Camera target it looks-at
    Vector3 up;       // Camera up vector (rotation over its axis)
    float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

    Camera constructToCamera() {
        Camera camera = {
            position,
            target,
            up,
            fovy,
            projection
        };
        return camera;
    }
};
class CameraComp
{
public:
    CameraComp(CameraData cameradata) : camera(cameradata.constructToCamera()) {

    }

    Vector3 getPosition()
    {
        return this->camera.position;
    }

    Vector3 getTarget()
    {
        return this->camera.target;
    }

    Vector3 getup()
    {
        return this->camera.up;
    }
    float getFOVY()
    {
        return this->camera.fovy;
    }

    float getProjection()
    {
        return this->camera.projection;
    }

    void setPosition(Vector3 value)
    {
        this->camera.position = value;
    }

    void setTarget(Vector3 value)
    {
        this->camera.target = value;
    }

    void setUp(Vector3 value)
    {
        this->camera.up = value;
    }

    void setFOVY(float value)
    {
        this->camera.fovy = value;
    }

    void setProjection(float value)
    {
        this->camera.projection = value;
    }

    Camera toCamera(CameraData data) {
        return data.constructToCamera();
    }

    Camera getSelfCamera() {
        return this->camera;
    }

    Camera* getSelfCameraPointer() {
        return &this->camera;
    }



private:

    Camera camera;
};
class Player : public GameObject
{
public:

    class Crosshair {
    public:
        Crosshair(int width, int height, Color color) : width(width), height(height), color(color) {
            position = { (float)width / 2, (float)height / 2 };
        }

        void Draw() {


        }

        int width, height;
        Color color;

        Vector2 position;
    };

    class Hand : public GameObject {

    public:


        Vector3 offset = Vector3Zero();
        Vector3 position = Vector3Zero();


        Item item;
        Hand(Model model) : offset({ 0.0f, 0.0f, 0.0f }) {

        }

        void onUpdate() override {

        }

        void onDestroy() const override {

        }

        int GetId() const override {
            return 0;
        }

        int GetType() const override {
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
               CAMERA_PERSPECTIVE });

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
        if (!IsKeyDown(KEY_LEFT_SHIFT)) {
            controller->isRunning = false;
            controller->SetSpeed(0.03f); //m/s
        }
        else {
            controller->isRunning = true;
            controller->SetSpeed(1.3f); //m/s
        }

        // View Sway


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
        // return PLAYER; // returns the player obj type
        return 0;
    }

    Model model; // Player model
    int cameraMode;

    bool doDraw = true;


    static void Setup() {

    }
    static inline CameraComp* cameraComponent;

    PlayerController* controller = new PlayerController(KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE, KEY_C, cameraMode);


    bool isRunning;

    static inline Hand* hand;
    Crosshair* crosshair;
    PlayerHealthComp* healthComp;


private:

    float SwayFactor;
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
    RayCollision collision = { 0 };

    // KeyboardKey *CurrentKeyDown;
    Vector3 position;
    Mesh mesh;

    // Global::ObjectTransform transform;
    Vector3 velocity;
    BoundingBox Box = GetModelBoundingBox(this->model);

    int m_max = STARTINGHP;
};