#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "lib/raylib.h"
#include "PlayerCamera.h"





class PlayerController 
{

    private:
        Vector3 m_position;
        Camera *camera;
        int m_mode;

    public:

        PlayerController(Camera camera) : camera(&camera) {}

        void UpdateValues(Camera *camera, int Mode) {}

        void CheckInput() {}
};