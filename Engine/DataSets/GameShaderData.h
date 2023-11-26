#pragma once
#include "../../../lib/raylib.h"

#include "../../Classes/Graphics/ShaderAttribute.h"

#include <vector>

using namespace std;


struct GameShaderData
{
    string name;
    Shader shader;
    const char *vertpath;
    const char *fragpath;    
};