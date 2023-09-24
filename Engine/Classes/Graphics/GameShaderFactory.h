#pragma once

#include "../../DataSets/Shader/GameShaderData.h"
#include "../Logging/Logman.h"


class GameShaderFactory
{
public:
    GameShaderFactory() {
        
    }

   
    Shader *ManufactureShader(GameShaderData shaderdata) {
        Logman::CustomLog(LOG_INFO, TextFormat("Manufacturing Shader %c", shaderdata.name), NULL);
        
        shaderdata.shader = LoadShader(shaderdata.vertpath, shaderdata.fragpath);

        return &shaderdata.shader;
    }

    void *ModifyShader(Shader shader, int loc, const void *Value, int UniformType) {
        SetShaderValue(shader, loc, Value, UniformType);
    }

};
