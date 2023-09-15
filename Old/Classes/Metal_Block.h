#pragma once
#include "lib/raylib.h"
#include "Gameobj.h"
#include "Logging/Logman.hpp"
#include "Monobehavior.h"

class Metal_Block : public GameObject
{
private:
    Vector3 m_position;

    Model m_model;

    Shader m_shader;
    Shader m_env_Cubemap = LoadShader("c:/Git/Minero/raylib/projects/VSCode/resources/cubemap.vs", "c:/Git/Minero/raylib/projects/VSCode/resources/cubemap.fs");

    Texture2D texture;

    const int id;

    const int ShaderValue = 7; // for the cubemap shader

    static bool m_areGraphicsInitialized;
    static bool m_isShadersInitialized;

    static void initShaders()
    {
        if (!m_isShadersInitialized)
        {

            m_isShadersInitialized = true;
        }
        else
        {
            Logman::CustomLog(LOG_WARNING, "Shaders for Metal blocks are already initialized!", NULL);
        }
    }

    void InitializeGraphics()
    {

        if (!m_areGraphicsInitialized)
        {
        }
        else
        {
            Logman::CustomLog(LOG_WARNING, "Graphics for a Metal_block instance is already initialized!", NULL);
        }
    }

    void SetShaders()
    {
    }

public:
    int GetId() const override
    {
        return this->id;
    }
    void onUpdate() override{

    };

    Metal_Block(Vector3 Position, Model model, Shader shader) : m_position(Position), m_model(model), m_shader(shader), id(RegisterObj(this))
    {
        Logman::CustomLog(LOG_INFO, "Static variables in Metal Block class, Performing first time operations", NULL);
        texture = LoadTextureFromImage(GenImageColor(texture.width, texture.height, GRAY));
        GenTextureMipmaps(&texture);
        SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

        m_model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = Global::MeshTools::GenTextureCubemap(m_env_Cubemap, texture, texture.width * texture.height, texture.format);

        m_model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = texture;
        m_model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 10.0f;

        // applying shader to model,
        this->m_model.materials[0].shader = m_shader;
        this->m_model.materials[1].shader = m_env_Cubemap;
    }
    Vector3 GetPosition() override
    {
        return this->m_position;
    }
    void Draw() override
    {

        DrawModel(this->m_model, m_position, 1.0f, WHITE);
    }

    int GetType() const override
    {
        return 0;
    }
};