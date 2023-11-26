#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "../../../lib/raylib.h"

#include "../Physics/Velocity.h"




class PlayerController 
{

    private:
        Vector3 position;
        
        // Velocity parameter.
        Velocity vel;


        CameraMode mode;
        
        KeyboardKey forward, backward, left, right, jump, crouch;
        
        std::thread Input(InputThread);
    public:


        void Update() {

        }

        // threaded
        void InputThread() {
            if (IsKeyDown(forward)) {
                // move the player forward
                
            }
        }

        PlayerController(KeyboardKey Forward, KeyboardKey Backward, KeyboardKey Left, KeyboardKey Right, KeyboardKey Jump, KeyboardKey Crouch, CameraMode mode) : forward(Forward), backward(Backward), left(Left), right(Right), jump(Jump), crouch(Crouch), mode(mode) {
            
        }

        
};