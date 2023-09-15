/*
    The sun class, referenced as just the Sun in the code, is going to be both the actor and the manager of the Standard Light shader. 
    As of 6/19/2023, this has not been implemented just yet. The goal is that when the day cycle is added, it will simply change the 
    ambient color to a darker shade of red/orange, until it is dark.
*/
#pragma once

#include "lib/raylib.h"
#include "lib/rlights.h"

class Sun {
    private:
        // positional values
        Vector3 m_position;
        Vector3 m_target;

        // shader values
        const Shader m_shader;
        Light m_light;
        Vector4 m_ambient_color;
        
        /*
        Rendering values
        this is just a value that stores what camera it should draw to, also it will be updated each frame. is static for memory saving sake        
        */ 
        static Camera *m_target_camera; 

    public:
        Sun(Vector3 sPosition, Vector3 sTarget, Shader shader, Vector4 ambient_Color) : m_position(sPosition), m_target(sTarget), m_shader(shader), m_ambient_color(ambient_Color) {};

        // will return the ambient color.
        Vector4 GetAmbient() {};

        void Update() {};

        ~Sun() {};
};