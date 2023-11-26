#pragma once

#include "../../../lib/raylib.h"
#include "../../DataSets/Globals.h"

class Environment {
    public:
        Environment() {
            
        }
        
        

        Texture2D Panorama;

        Shader shdrCubemap;
        Shader shdrLighting;
        Shader shdrReflection;
};