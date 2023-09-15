#include "Player.h"
#include "Gameobj.h"
#include "lib/raymath.h"
#include "lib/raylib.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>


void Player::onCollision() const {

}

void Player::onUpdate() const {
    std::thread keywatch(CheckInput);
    keywatch.join();

    if (CheckCollision(this->GetBoundingBox()))
    {
        this->onCollision();
    } else {
        velocity += (Vector3){ 0.0f, GRAVITATIONAL_CONSTANT * Global::Time::DeltaTime(), 0.0f};
    }


}

void Player::onDestroy() const {
    delete this;
}

BoundingBox Player::GetBoundingBox() const {
    return Global::BoxNull;
}

void Player::Draw() const
{

    if (cameraMode != CAMERA_FIRST_PERSON)
    {
    }
    else
    {
        
        DrawModel(model, m_camera.position, 0.2f, GREEN);
    }
}

Player::~Player()
{
    UnloadModel(model);
}



void Player::PlayFootsteps()
{
}

int Player::GetType() const 
{
    return PLAYER; // returns the player obj type
} 

void CheckInput()
{


    while (!WindowShouldClose())
    {
        // Checks for player movement
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_D))
        {
            // @todo update function to be compatible with static
            bool FootstepPlaying = IsSoundPlaying(Footstep_Grass);
            if (!FootstepPlaying)
            {
                
                if (cameraMode != CAMERA_FIRST_PERSON)
                {
                    // to make it sound more realistic, the volume will be random
                    float volume = GetRandomValue(80, 100) / 100.0f;
                    // calculate a random pitch between 0.8 and 1.2
                    float pitch = GetRandomValue(80, 120) / 100.0f;

                    MemAlloc(pitch);
                    MemAlloc(volume);
                    // play the footstep sound with the random volume and pitch
                    PlaySound(Footstep_Grass);
                    SetSoundPitch(Footstep_Grass, pitch + Vector3Distance(this->m_camera.position, this->m_camera.target) / PI);
                    SetSoundVolume(Footstep_Grass, volume + Vector3Distance(this->m_camera.position, this->m_camera.target) / PI);
                    MemFree(&pitch);
                    MemFree(&volume);
                }
                else
                {
                    // to make it sound more realistic, the volume will be random
                    float volume = GetRandomValue(80, 100) / 100.0f;
                    // calculate a random pitch between 0.8 and 1.2
                    float pitch = GetRandomValue(80, 120) / 100.0f;

                    // play the footstep sound with the random volume and pitch
                    PlaySound(Footstep_Grass);
                    SetSoundPitch(Footstep_Grass, pitch);
                    SetSoundVolume(Footstep_Grass, volume);
                }
            }
        }
        // Switch camera mode
        if (IsKeyPressed(KEY_ONE))
        {

            this->cameraMode = CAMERA_FREE;
            this->m_camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Reset roll
        }

        if (IsKeyPressed(KEY_TWO))
        {
            this->cameraMode = CAMERA_FIRST_PERSON;
            this->m_camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Reset roll
        }

        if (IsKeyPressed(KEY_THREE))
        {
            this->cameraMode = CAMERA_THIRD_PERSON;
            this->m_camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Reset roll
        }

        if (IsKeyPressed(KEY_FOUR))
        {
            this->cameraMode = CAMERA_ORBITAL;
            this->m_camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Reset roll
        }
    }
}