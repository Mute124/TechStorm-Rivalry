#pragma once

#include "../../../../lib/raylib.h"

class ShadowMap {
    public:
        ShadowMap();

        void BeginMapping() {
            BeginTextureMode(shadowMap);
        }

        void EndMapping() {
            EndTextureMode();
        }

        RenderTexture GetShadowMap() {
            return shadowMap;
        }

        void CreateShadowMap(int width, int height) {
            
        }

    private:
        RenderTexture shadowMap;
};