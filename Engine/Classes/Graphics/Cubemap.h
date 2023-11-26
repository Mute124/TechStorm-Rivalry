#pragma once

#include "../../../lib/raylib.h"
#include "Matmap.h"

class Cubemap {
    public:

        Cubemap(Texture2D image, CubemapLayout layout, TextureCubemap cubemap) : layout(layout), panorama(image) {

        }

        void Kill() {
            UnloadTexture(panorama);
            delete this;
        }

        ~Cubemap() {

        }

        bool UseHDR() {
            return useHDR;
        }

        void SetHDR(bool value) {
            useHDR = value;
        }


        static void SetCubemapShaderFromShader(Shader shader) {
            CubemapShader = shader;
        }

        static void SetCubemapShaderFromFile(const char *vs, const char *fs) {
            CubemapShader = LoadShader(vs, fs);
        }

        const static int ENVIRONMENTMAP = 7;
        const static int DOGAMMA = 1;
        const static int VFLIPPED = 0;

        static Shader CubemapShader = {0};

        bool useHDR;

        CubemapLayout layout;
        TextureCubemap cubemapTexture;
        Texture2D panorama;

        
};