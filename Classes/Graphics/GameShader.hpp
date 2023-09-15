#pragma once
#include "../lib/raylib.h"


class GameShader : public Shader{
    public:
        GameShader();
        
        bool isShaderReady() {
            return isReady;
        };

        virtual void EnableShader() {
            BeginShaderMode();
        };

        virtual void DisableShader() {};

        // Assign shader
        Shader AssignShader() {
            Shader shader = { 0 };
            
        };

        virtual void Start() {};

    private:
        
        bool isReady;

};