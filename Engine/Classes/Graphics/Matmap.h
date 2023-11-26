#pragma once
#include "../../../lib/raylib.h"

#define MAX_MAPS 25
#define MAX_MAPS_PER_OBJECT 10

class Matmap {
    public:

        Matmap() {}

        ~Matmap() {
            delete this;
        }

        void AppendTexture(Texture2D texture, MaterialMapIndex TargetMap) {
            maps[TargetMap]->texture = texture;
        }

        void StripTexture(MaterialMapIndex TargetMap) {
            maps[TargetMap]->texture = LoadTextureFromImage(GenImageChecked(maps[TargetMap]->texture.width, maps[TargetMap]->texture.height, maps[TargetMap]->texture.width / 2, maps[TargetMap]->texture.height / 2, PINK, BLACK));
        }

        void AppendMaterial(MaterialMap Map, MaterialMapIndex MapType) {
            maps[MapType] = &Map;
        }

        void StripMaterial(MaterialMapIndex MapType) {
            maps[MapType] = nullptr;
        }

        void AddShaderFromShader(Shader shader) {
            this->objectShader = shader;
        }

        void AddShaderFromFile(const char *vs, const char *fs) {
            this->objectShader = LoadShader(vs, fs);

        }

        void AddShaderFromText(const char *vscode, const char *fscode) {
            this->objectShader = LoadShaderFromMemory(vscode, fscode);
        }

        Material GenerateMaterial() {
            Material mat;

            mat.maps = maps;

            mat.shader = this->objectShader;

            return mat;
        }





    private:
        

        
        Shader objectShader;

        float roughness;
        float specular;

        Color Diffuse;

        MaterialMap *maps[MAX_MAPS_PER_OBJECT];

        Texture2D *textures[MAX_MAPS_PER_OBJECT];
};