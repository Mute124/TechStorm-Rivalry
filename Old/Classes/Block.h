/*
    this class needs to be migrated to be a base class that polymorphism takes place in.
*/
#pragma once
#include "lib/raylib.h"

#include "lib/glm/glm/glm.hpp"
#include "Gameobj.h"
#include "Globals.h"
#include "Monobehavior.h"

#include <stdio.h>
#include <stdlib.h>


// specifies all the codes for the different block types. just makes things easier :)
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

        DrawBoundingBox(this->Box, ORANGE);
        if (this->type != BlockAir)
        {
            
            //BeginShaderMode(this->shader);
            
            DrawModel(model, m_position, BLOCK_SIZE, color);
            //EndShaderMode();

            //BeginShaderMode(this->test);
            //DrawModel(model, m_position, BLOCK_SIZE, color);
            //EndShaderMode();
            
        }
    }
    
    Shader test;

    // main block constructor.
    Block(const BType type, Vector3 position, const Color color, Shader shader, Model model) : type(type), color(color), m_position(position), shader(shader), model(model), id(RegisterObj(this)), velocity(Vector3Zero()), Box(GetModelBoundingBox(this->model))
    {

        Logman::CustomLog(LOG_TRACE, "Block Constructor", NULL);
        this->shader = shader;
        
        this->model.materials[0].shader = shader;
        this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(this->shader, "viewPos");
        this->model = model;
        const static Texture2D Bricks = LoadTexture("C:/Git/Minero/raylib/projects/VSCode/resources/textures/Brick.png");

        const static Texture2D Bricks_Normal = LoadTexture("C:/Git/Minero/raylib/projects/VSCode/resources/textures/Brick_normals.png");
        
        SetTextureFilter(Bricks, TEXTURE_FILTER_ANISOTROPIC_16X);
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].value = 1.0f;
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = color;

        this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 1.0f;

        SetShaderValue(shader, GetShaderLocation(shader, "colDiffuse"), &color, SHADER_UNIFORM_VEC4);
        
        test = LoadShader("resources/cubemap.vert", "resources/cubemap.frag");
        test.locs[SHADER_LOC_MATRIX_VIEW] = GetShaderLocation(test, "view");
        SetShaderValue(test, test.locs[SHADER_LOC_MATRIX_VIEW], &this->model.transform, UNIFORM_VEC4);

        this->model.materials[1].shader = test;




        
    }

    // main block constructor.
    Block(const BType type, Vector3 position, const Color color, Shader shader) : type(type), color(color), m_position(position), shader(shader), model(model), id(RegisterObj(this)), velocity(Vector3Zero()), Box(GetModelBoundingBox(this->model))
    {

        Logman::CustomLog(LOG_TRACE, "Block Constructor", NULL);
        this->shader = shader;
        
        this->model.materials[0].shader = shader;
        this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(this->shader, "viewPos");
        this->model = model;
        const static Texture2D Bricks = LoadTexture("C:/Git/Minero/raylib/projects/VSCode/resources/textures/Brick.png");

        const static Texture2D Bricks_Normal = LoadTexture("C:/Git/Minero/raylib/projects/VSCode/resources/textures/Brick_normals.png");
        
        SetTextureFilter(Bricks, TEXTURE_FILTER_ANISOTROPIC_16X);
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].value = 1.0f;
        this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = color;

        this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = Bricks;
        this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 1.0f;

        SetShaderValue(shader, GetShaderLocation(shader, "colDiffuse"), &color, SHADER_UNIFORM_VEC4);
        
        test = LoadShader("resources/cubemap.vert", "resources/cubemap.frag");
        test.locs[SHADER_LOC_MATRIX_VIEW] = GetShaderLocation(test, "view");
        SetShaderValue(test, test.locs[SHADER_LOC_MATRIX_VIEW], &this->model.transform, UNIFORM_VEC4);

        this->model.materials[1].shader = test;




        
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

    void onUpdate() override
    {

        if (CheckCollision(this, this->id))
        {
            this->colpos = this->m_position;
            this->onCollision();
            this->isColliding = true;
            this->velocity = Vector3Zero();
            BeginDrawing();

            EndDrawing();
        }
        else
        {

            this->velocity = Vector3Subtract(this->velocity, (Vector3){0.0f, 0.001f * (float)Global::Time::GetGameTime(), 0.0f});
        }

        this->m_position = Vector3Add(this->m_position, this->velocity);
    };

    Vector3 GetPosition() override
    {
        return this->m_position;
    }
    static void UpdateBlockRegistry(std::vector<GameObject *> objects)
    {
        objectreg = objects;
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

        return glm::vec3(m_position.x, m_position.y, m_position.z);
    }

    glm::vec3 GetMaxBounds() const
    {
        return glm::vec3(m_position.x + BLOCK_SIZE, m_position.y + BLOCK_SIZE, m_position.z + BLOCK_SIZE);
    }

    glm::vec3 GetCenter() const
    {
        return glm::vec3(m_position.x + BLOCK_SIZE / 2, m_position.y + BLOCK_SIZE / 2, m_position.z + BLOCK_SIZE / 2);
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

    static inline Model DefaultBlockModel = LoadModelFromMesh( GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

private:
    RenderTexture2D ee;
    Vector3 colpos;
    bool initial = true;
    bool isColliding = false;
    static inline std::vector<GameObject *> objectreg;
    BlockType type; // specifies what type of block it is. see above enum for types.

    Color color; // color of the block, Right now not being used

    objtype objecttype = BLOCK; // just boilerplate

    Texture2D texture;

    bool m_deleteRequested; // currently unused, since it only takes 1 bit, this isnt gonna be deleted just yet.

    const Mesh m_mesh = GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

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

    Vector3 m_position; // position of the block

    Model model;
    Shader shader;
    Shader m_shader_cubemap;

    Transform transform;

    BoundingBox Box;

    Vector3 velocity;

    const int id;

    Vector2 ScreenPosition = {0.0f, 0.0f};
};