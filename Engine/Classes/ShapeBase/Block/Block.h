/*
   TODO : this class needs to be migrated to be a base class that polymorphism takes place in. Also make the code not crap
*/
#pragma once

#include "../../../../lib/raylib.h"
#include "../../../../lib/glm/glm/glm.hpp"
#include "../../GameObject/Gameobject.h"
#include "../../../DataSets/Globals.h"
#include "../../Project/Game/Game.h"


#include <stdio.h>
#include <stdlib.h>

// specifies all the codes for the different block types.
typedef enum BlockType
{
    BlockAir = 0,
    BlockGrass,
    BlockDirt,
    BlockStone,
    BlockBrick,
    BlockMetal
} BType;

// The class for, well blocks!
class Block : public GameObject
{

public:
    // Automatically sends it to the renderer.
    void Draw() override
    {

        // DrawBoundingBox(this->Box, ORANGE);
        if (this->type != BlockAir)
        {
            
            //BeginShaderMode(shader);
            DrawModel(model, position, BLOCK_SIZE, color);
            //EndShaderMode();
            //BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);

            //DrawModel(model, position, BLOCK_SIZE, color);
            //EndBlendMode();
        }
    }

    // main block constructor.
    Block(const BType type, Vector3 position, const Color color, Shader shader, Model model) : type(type), color(color), position(position), shader(shader), model(model), id(RegisterObj(this)), velocity(Vector3Zero()), Box(GetModelBoundingBox(this->model))
    {

        Logman::CustomLog(LOG_TRACE, "Block Constructor", NULL);
        this->shader = shader;
        this->model = model;

        const static Texture2D Bricks = LoadTexture("resources/textures/Brick.png");
        SetTextureFilter(Bricks, TEXTURE_FILTER_BILINEAR);
        SetTextureWrap(Bricks, TEXTURE_WRAP_CLAMP);

        const static Texture2D BrickNormal = LoadTexture("resources/textures/Block/Brick/Brick_NORM.png");

        const static Texture2D BrickSpecular = LoadTexture("resources/textures/Block/Brick/Brick_SPEC.png");

        this->model.materials[0].shader = shader;
        this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(this->shader, "viewPos");

        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = BrickNormal;
        this->model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = BrickSpecular;
       // this->model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = Global::MeshTools::GenTextureCubemap(Game::Renderer::env->shdrCubemap, Game::Renderer::env->Panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        
        const float roughness = 1.0f;
        SetShaderValue(this->model.materials[0].shader, GetShaderLocation(this->model.materials[0].shader, "texture0"), &Bricks, SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(this->model.materials[0].shader, GetShaderLocation(this->model.materials[0].shader, "roughness"), &roughness, SHADER_UNIFORM_FLOAT);


        // SetShaderValueMatrix(this->model.materials[0].shader, GetShaderLocation(this->model.materials[0].shader, "matModel"), this->model.transform);
        SetShaderValueMatrix(this->model.materials[0].shader, GetShaderLocation(this->model.materials[0].shader, "mvp"), this->model.transform);



        
        // UnloadTexture(Bricks);
    }
    // main block constructor.

    int GetId() const override
    {
        return this->id;
    }
    int GetType() const override
    {

        return BLOCK;
    }

    Model getModel()
    {
        return this->model;
    }

    void SetBlockShaderValue(int locIndex, const void *value, int UniformType)
    {
        SetShaderValue(shader, locIndex, &value, UniformType);
    }

    void onUpdate() override
    {

        if (CheckCollision(this, this->id))
        {
            this->colpos = this->position;
            this->onCollision();
            this->isColliding = true;
            this->velocity = Vector3Zero();
        }
        else
        {

            this->velocity = Vector3Subtract(this->velocity, (Vector3){0.0f, 0.001f * (float)Global::Time::GetGameTime(), 0.0f});
        }

        this->position = Vector3Add(this->position, this->velocity);
    };

    Vector3 GetPosition() override
    {
        return this->position;
    }

    BoundingBox GetBoundingBox() override
    {

        return this->Box;
    };

    void onCollision() override{

    };

    void onDestroy() const override
    {
        delete this;
    };

    // does what it says. it just breaks a block, can be overridden to have custom behavior
    virtual void Break()
    {
        type = BlockAir; // turns it to air essentially.
    }

    // deconstructor. DO NOT TOUCH OR I SWEAR TO GOD!
    virtual ~Block()
    {
        UnRegisterObj(this->id);
        m_deleteRequested = true;
    }

    // GLM functions are NOT useless. they are used to detect block breaking
    glm::vec3 GetMinBounds() const
    {

        return glm::vec3(position.x, position.y, position.z);
    }

    glm::vec3 GetMaxBounds() const
    {
        return glm::vec3(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE, position.z + BLOCK_SIZE);
    }

    glm::vec3 GetCenter() const
    {
        return glm::vec3(position.x + BLOCK_SIZE / 2, position.y + BLOCK_SIZE / 2, position.z + BLOCK_SIZE / 2);
    }

    struct AABB
    {
        glm::vec3 min_bounds;
        glm::vec3 max_bounds;
    };

    BoundingBox GetBounds() const
    {
        Vector3 minBounds = {GetMinBounds().x, GetMinBounds().y, GetMinBounds().z};
        Vector3 maxBounds = {GetMaxBounds().x, GetMaxBounds().y, GetMaxBounds().z};
        return {minBounds, maxBounds};
    }

    Vector3 colpos;
    bool initial = true;
    bool isColliding = false;

    BlockType type; // specifies what type of block it is. see above enum for types.

    Color color; // color of the block, Right now not being used

    objtype objecttype = BLOCK; // just boilerplate

    Texture2D texture;

    bool m_deleteRequested; // currently unused, since it only takes 1 bit, this isnt gonna be deleted just yet.

    const Mesh mesh = GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

    // currently unused, this was supposed to be a break block method.
    bool ShouldDelete()
    {
        if (this->m_deleteRequested)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vector3 position; // position of the block

    Model model;
    Shader shader;
    Shader m_shader_cubemap;

    //ObjectTransform transform;

    BoundingBox Box;

    Vector3 velocity;

    const int id;

};