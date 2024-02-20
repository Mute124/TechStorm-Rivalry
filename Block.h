/*
   TODO : this class needs to be migrated to be a base class that polymorphism takes place in. Also make the code not crap
*/
#pragma once

#include "common.h"
#include "Gameobject.h"
#include "Game.h"

#include <stdio.h>
#include <stdlib.h>


// The class for, well blocks!
class Block : public GameObject
{
public:
	// Automatically sends it to the renderer.
	void draw() override
	{
			DrawModel(model, position, 1.0f, color);
	}


	
	// main block constructor.
	Block(Vector3 position, const Color color, Shader shader, Model model) : color(color), position(position), model(model)
	{
		Logman::customLog(LOG_TRACE, "Block Constructor", NULL);
		this->model = model;

		const static Texture2D Bricks = LoadTexture("resources/textures/Block/Brick/Brick.png");
		this->model.materials[0].shader = shader;


		// why the fuck does PBR lighting not work on AMD cards but not nvidia?? 
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
		this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
		this->model.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
		this->model.materials[0].maps[MATERIAL_MAP_EMISSION].color = Color{ 255, 162, 0, 100 };

		this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/textures/Block/Brick/brickMRAO.png");
		this->model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/textures/Block/Brick/brick_NORM.png");
		this->model.materials[0].maps[MATERIAL_MAP_HEIGHT].texture = LoadTexture("resources/textures/Block/Brick/brick_DISP.png");
		this->model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = LoadTexture("resources/textures/Block/Brick/brick_SPEC.png");

		
		//this->model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = LoadTexture("resources/textures/Old_Car/old_car_e.png");
		/*
		*
		*
		*
		*
		*
		*         this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/textures/Old_Car/old_car_d.png");
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/textures/Old_Car/old_car_mra.png");
		this->model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/textures/Old_Car/old_car_n.png");

				// Setup materials[0].maps default parameters

		//

		// Setup materials[0].maps default textures
   //

		// Setup materials[0].maps default textures

	*/

	// UnloadTexture(Bricks);
	}


	void onUpdate() override
	{
	};

	void onDestroy() const override
	{
		delete this;
	};


	// deconstructor. DO NOT TOUCH OR I SWEAR TO GOD!
	virtual ~Block()
	{
		deleteRequested = true;
	}


	Color color; // color of the block, Right now not being used

	bool deleteRequested; // currently unused, since it only takes 1 bit, this isnt gonna be deleted just yet.
	static inline Vector2 blockTextureTiling = Vector2{ 0.5f, 0.5f };

	const Mesh mesh = GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
	Vector3 position; // position of the block
	Model model;
};