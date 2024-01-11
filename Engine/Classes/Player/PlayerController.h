#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "../../../common.h"


//#define CAMERA_IMPLEMENTATION

class PlayerController
{

private:
    
    int mode;

    float speed;

    float mouseSensitivity = 0.05f;

    KeyboardKey forward, backward, left, right, jump, crouch;
public:
    
    bool isRunning = false;
    bool canMove = true;
    bool isGrounded = false;

    PlayerController(KeyboardKey Forward, KeyboardKey Backward, KeyboardKey Left, KeyboardKey Right, KeyboardKey Jump, KeyboardKey Crouch, int mode) : forward(Forward), backward(Backward), left(Left), right(Right), jump(Jump), crouch(Crouch), mode(mode)
    {
        
    }



    void SetSpeed(float speed) {
        this->speed = speed;
    }

    void Update(Camera *camera)
    { 
        
        // Camera PRO usage example (EXPERIMENTAL)
        // This new camera function allows custom movement/rotation values to be directly provided
        // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
        UpdateCameraPro(camera,
            Vector3{
                (IsKeyDown(forward) || IsKeyDown(KEY_UP))*speed -      // Move forward-backward
                (IsKeyDown(backward) || IsKeyDown(KEY_DOWN))*speed,    
                (IsKeyDown(right) || IsKeyDown(KEY_RIGHT))*speed -   // Move right-left
                (IsKeyDown(left) || IsKeyDown(KEY_LEFT))*speed,
                0.0f                                                // Move up-down
            },
            Vector3{
                GetMouseDelta().x*mouseSensitivity,                            // Rotation: yaw
                GetMouseDelta().y*mouseSensitivity,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            },

            GetMouseWheelMove()*2.0f);                              // Move to target (zoom)
    }



};