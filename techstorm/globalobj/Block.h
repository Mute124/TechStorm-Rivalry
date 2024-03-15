/*
   TODO : this class needs to be migrated to be a base class that polymorphism takes place in. Also make the code not crap
*/
#pragma once

#include "../common.h"
#include "../Game.h"
#include "../core/ui/UIElement.h"
#include <stdio.h>
#include <stdlib.h>

// The class for, well blocks!
class Block : public GameObject
{
public:

	void draw() override {
		DrawModel(this->model, this->position, 1.0f, WHITE);
	}
	// main block constructor.
	Block(Vector3 position, const Color color, Shader shader, Model model)
	{
		Logman::customLog(LOG_TRACE, "Block Constructor", NULL);

		this->threadSafe = true;

		this->model = model;
		this->tint = color;
		this->position = position;
		this->shdr = shader;
		const static Texture2D Bricks = LoadTexture("resources/textures/Block/Brick/Brick.png");
		this->model.materials[0].shader = shader;

		// why the fuck does PBR lighting not work on AMD cards but not nvidia??
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;
		this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
		this->model.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
		this->model.materials[0].maps[MATERIAL_MAP_EMISSION].color = Color{ 255, 162, 0, 100 };

		//		this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/textures/Block/Brick/brickMRAO.png");
		this->model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/textures/Block/Brick/brick_NORM.png");
		this->model.materials[0].maps[MATERIAL_MAP_HEIGHT].texture = LoadTexture("resources/textures/Block/Brick/brick_DISP.png");
		this->model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = LoadTexture("resources/textures/Block/Brick/brick_SPEC.png");
	}

	void onUpdate() override
	{
	};

	void onDestroy() const override {
	};

	// deconstructor. DO NOT TOUCH OR I SWEAR TO GOD!
	virtual ~Block()
	{
		delete this;
	}
	static inline Vector2 blockTextureTiling = Vector2{ 0.5f, 0.5f };
};
