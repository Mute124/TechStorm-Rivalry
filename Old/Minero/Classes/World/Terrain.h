#pragma once
#include "../../../Engine/Classes/GameObject/Gameobject.h"

#include "../../../lib/raylib.h"
#include "../../../lib/rlgl.h"
#include "../../../lib/raymath.h"

#include "../../../Engine/Classes/Graphics/Shaders/ClipShader.h"
#include "../../../Engine/Classes/Graphics/RenderFactory.h"
#include "../../../Engine/Classes/Project/Game/Game.h"
#include "../../../Engine/DataSets/Globals.h"

#include <vector>

class Terrain : public GameObject
{
public:
    Terrain(ObjectTransform transform, const Color color) : id(RegisterObj(this)), transform(transform), col(color)
    {
        Image initialHeightmapImage = GenImagePerlinNoise(MAP_RESOLUTION, MAP_RESOLUTION, 50, 50, 4.0f); // generate fractal perlin noise
        mapData = new std::vector<float>(MAP_RESOLUTION * MAP_RESOLUTION);
        
        // Extract pixels and put them in mapData
        Color *pixels = LoadImageColors(initialHeightmapImage);
        for (size_t i = 0; i < MAP_RESOLUTION * MAP_RESOLUTION; i++)
        {
            mapData->at(i) = pixels[i].r / 255.0f;
        }

        // Update pixels from mapData to texture
        for (size_t i = 0; i < MAP_RESOLUTION * MAP_RESOLUTION; i++)
        {
            int val = mapData->at(i) * 255;
            pixels[i].r = val;
            pixels[i].g = val;
            pixels[i].b = val;
            pixels[i].a = 255;
        }
        Image heightmapImage = LoadImageEx(pixels, MAP_RESOLUTION, MAP_RESOLUTION);
        Texture2D heightmapTexture = LoadTextureFromImage(heightmapImage); // Convert image to texture (VRAM)
        UnloadImage(heightmapImage);                                       // Unload heightmap image from RAM, already uploaded to VRAM
        SetTextureFilter(heightmapTexture, TEXTURE_FILTER_BILINEAR);
        SetTextureWrap(heightmapTexture, TEXTURE_WRAP_CLAMP);
        GenTextureMipmaps(&heightmapTexture);

        // TERRAIN
        Mesh terrainMesh = GenMeshPlane(32, 32, 256, 256);                        // Generate terrain mesh (RAM and VRAM)
        Texture2D terrainGradient = LoadTexture("resources/terrainGradient.png"); // color ramp of terrain (rock and grass)

        // SetTextureFilter(terrainGradient, FILTER_BILINEAR);
        SetTextureWrap(terrainGradient, TEXTURE_WRAP_CLAMP);
        GenTextureMipmaps(&terrainGradient);

        terrainModel = LoadModelFromMesh(terrainMesh)
        terrainModel.transform = MatrixTranslate(0, -1.2f, 0);
        terrainModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = terrainGradient;
        terrainModel.materials[0].maps[MATERIAL_MAP_NORMAL].texture = heightmapTexture;
        terrainModel.materials[0].shader = LoadShader("resources/shaders/terrain.vert", "resources/shaders/terrain.frag");

        // Get some shader loactions
        terrainModel.materials[0].shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(terrainModel.materials[0].shader, "matModel");
        terrainModel.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(terrainModel.materials[0].shader, "viewPos");
        int terrainDaytimeLoc = GetShaderLocation(terrainModel.materials[0].shader, "daytime");
        int cs = ClipShader::AddClipShader(terrainModel.materials[0].shader); // register as clip shader for automatization of clipPlanes
        float param10 = 0.0f;
        int param11 = 2;
        SetShaderValue(terrainModel.materials[0].shader, ClipShader::clipShaderHeightLocs[cs], &param10, SHADER_UNIFORM_FLOAT);
        SetShaderValue(terrainModel.materials[0].shader, ClipShader::clipShaderTypeLocs[cs], &param11, SHADER_UNIFORM_INT);

        // ambient light level
        int terrainAmbientLoc = GetShaderLocation(terrainModel.materials[0].shader, "ambient");
        SetShaderValue(terrainModel.materials[0].shader, terrainAmbientLoc, Game::ambientShader->ambc, SHADER_UNIFORM_VEC4);
        Texture2D rockNormalMap = LoadTexture("resources/rockNormalMap.png"); // normal map
        SetTextureFilter(rockNormalMap, TEXTURE_FILTER_BILINEAR);
        GenTextureMipmaps(&rockNormalMap);
        terrainModel.materials[0].shader.locs[SHADER_LOC_MAP_ROUGHNESS] = GetShaderLocation(terrainModel.materials[0].shader, "rockNormalMap");
        terrainModel.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = rockNormalMap;
    }

    ~Terrain()
    {
        delete this;
    }

    void Draw() override
    {
        RenderFactory::ManufactureScene(Game::player->cameraComponent->getSelfCamera(), NULL, {terrainModel, transform,})
    }

private:
    std::vector<float> *mapData;
    const int id;
    ObjectTransform transform;
    const Color col;
    Model terrainModel; // Load model from generated mesh
};