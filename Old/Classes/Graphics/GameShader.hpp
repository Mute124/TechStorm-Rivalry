#pragma once
#include "../lib/raylib.h"

struct ObjectShader : public Shader
{
    /* data */
    Shader *shader = new Shader();
    // default deconstructor
    ~ObjectShader()  {
        delete shader;
    }
};
class GameShader : public ObjectShader
{
public:
    GameShader() {
        
    };

    bool isShaderReady()
    {
    };

    virtual void EnableShader()
    {
        
    };

    virtual void DisableShader() {};

    virtual void UnloadGameShader() {}
private:

    bool isReady;
};