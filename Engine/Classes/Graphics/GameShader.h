#pragma once
#include "../../../lib/raylib.h"





class GameShader {
    public:
        GameShader() {
            
        };
        
        bool isShaderReady() {
            return isReady;
        };

        virtual void EnableShader() {
            BeginShaderMode();
        };

        virtual void DisableShader() {};


        virtual void Start() {};

    private:
        
        bool isReady;

};