#pragma once

#include "../../../../lib/raylib.h"

#include "../../../../lib/rlights.h"

class LightObject {
    public:
        
        LightObject(int type, Vector3 pos, Vector3 targ, Color color, Shader shader) {

            this->lightcomp = CreateLight(type, pos, target, color, shader);

            RegisterLight(this->lightcomp);     
        }
        
        Light lightcomp;
    private:

        // registers a new light, since we want the ambiance to be affected by all lights
        void RegisterLight(Light light) {
            ambiance += light.color;
        }
        
        // All light colors added together to simulate world lighting
        static inline Color ambiance;

        
};