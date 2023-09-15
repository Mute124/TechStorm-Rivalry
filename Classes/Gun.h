#pragma once
#include "lib/raylib.h"
#include "lib/raymath.h"
#include "Gameobj.h"
#include "Globals.h"


#include <C:\Git\Minero\w64devkit\lib\gcc\x86_64-w64-mingw32\12.2.0\include\c++\stdlib.h>

class Gun
{
private:
    Vector3 m_position;
    Camera m_player_cam;
    Model m_model;
    Shader shader;
    Shader m_cubemap_shader;

    const int ShaderValue = 7; // for the cubemap shader

    void LoadGunModel()
    {
        this->m_model = LoadModel("C:/Git/Minero/raylib/projects/VSCode/resources/models/Bad_Gun.obj");
        this->m_model.materials[0].shader = this->shader;
        this->m_model.materials[1].shader = this->m_cubemap_shader;
        this->m_model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.2f;
        Image img = GenImageColor(16, 16, GRAY);
        this->m_model.materials[1].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
            img, CUBEMAP_LAYOUT_AUTO_DETECT); // CUBEMAP_LAYOUT_PANORAMA;

        SetShaderValue(this->m_model.materials[1].shader, GetShaderLocation(this->m_model.materials[0].shader, "environmentMap"), &ShaderValue,
            SHADER_UNIFORM_INT);
        UnloadImage(img);
    }
public:
    
    

    Gun(Camera PlayerCam, Shader shader, Shader Cubemap) : m_player_cam(PlayerCam), shader(shader), m_cubemap_shader(Cubemap) {};

    void Draw() {};
    ~Gun() {}
};