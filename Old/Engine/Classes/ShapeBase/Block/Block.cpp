
#include "Block.h"
#include "Gameobj.h"
#include "Monobehavior.h"
#include "lib/raymath.h"

/**
 * Draws the block if it is not of type BlockAir.
 *
 * @throws none
 */
void Block::Draw() const
{
    if (this->type != BlockAir)
    {
        DrawModel(model, position, BLOCK_SIZE, color);
    }
}

Block::~Block()
{
}

/**
 * Initialize the Block.
 *
 * @throws None
 */
void Block::onCollision() const
{
    velocity = Vector3Zero();
    
}

void Block::onUpdate() const
{

}
/**
 * Get the model of the block.
 *
 * @return the model of the block
 */
Model Block::getModel()
{
    return this->model;
}


/**
 * Breaks the block by setting its type to BlockAir.
 *
 * @throws ErrorType A description of the error that might occur.
 */
void Block::Break()
{
    type = BlockAir; // turns it to air essentially.
}

/**
 * Get the type of the block.
 *
 * @return the type of the block
 */
int Block::GetType() const
{
    return 0;
}

struct AABB
{
    glm::vec3 min_bounds;
    glm::vec3 max_bounds;
};

/**
 * Retrieves the bounding box of the Block object.
 *
 * @return A BoundingBox object representing the minimum and maximum bounds of the block.
 *
 * @throws None
 */
BoundingBox Block::GetBounds() const
{
    Vector3 minBounds = {GetMinBounds().x, GetMinBounds().y, GetMinBounds().z};
    Vector3 maxBounds = {GetMaxBounds().x, GetMaxBounds().y, GetMaxBounds().z};
    return {minBounds, maxBounds};
}

/**
 * Get the minimum bounds of the block.
 *
 * @return A vector representing the minimum bounds.
 */
glm::vec3 Block::GetMinBounds() const
{

    return glm::vec3(position.x, position.y, position.z);
}

glm::vec3 Block::GetMaxBounds() const
{
    return glm::vec3(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE, position.z + BLOCK_SIZE);
}

glm::vec3 Block::GetCenter() const
{
    return glm::vec3(position.x + BLOCK_SIZE / 2.0f, position.y + BLOCK_SIZE / 2.0f, position.z + BLOCK_SIZE / 2.0f);
}

Block::Block(const BType type, Vector3 position, const Color color, Shader shader, Model model) : type(type), color(color), position(position), shader(shader), model(model)
{
    this->shader = shader;
    this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(this->shader, "viewPos");
    this->model = model;
    this->model.materials[0].shader = shader;
    Texture2D Base = LoadTextureFromImage(GenImageColor(2, 2, BLUE));

    this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Base;

    this->model.materials[0].maps[MATERIAL_MAP_EMISSION].color = RED;

    this->shader = this->model.materials->shader;
    RegisterObj();
}
