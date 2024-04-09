/*
   TODO : this class needs to be migrated to be a base class that polymorphism takes place in. Also make the code not crap
*/
#pragma once

#include "../common.h"
#include "../Game.h"
#include "../core/ui/UIElement.h"
#include <stdio.h>
#include <stdlib.h>

namespace TechStormRivalry {

	// The class for, well blocks!
	class Block : public TechStorm::GameObject
	{
	public:

		void draw() override {

			//DrawSphere(this->position, 5.0f, RED);
			DrawModel(this->model, this->position, 1.0f, this->tint);
		}

		// main block constructor.
		Block(Vector3 position, const Color color, Shader shader, Model model)
		{
			TechStorm::Logman::customLog(LOG_TRACE, "Block Constructor", NULL);
			Shader test = LoadShader("resources/shaders/tpbr.vert", "resources/shaders/tpbr.frag");
			this->threadSafe = true;
			this->isDynamic = true;
			this->model = model;
			this->tint = color;
			this->position = position;
			this->shdr = test;
			const static Texture2D Bricks = LoadTexture("resources/textures/metalAlb.png");
			this->model.materials[0].shader = shader;

			// why the fuck does PBR lighting not work on AMD cards but not nvidia??
			//this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
			//this->model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
			//this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
			//this->model.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;

			//this->model.materials[0].maps[MATERIAL_MAP_EMISSION].color = color;

			//		this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
			//this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = Bricks;
			//this->model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/textures/mra.png");
			//this->model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/textures/metalNorm.png");
			//this->model.materials[0].maps[MATERIAL_MAP_HEIGHT].texture = LoadTexture("resources/textures/metalHeight.png");

			//this->model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = LoadTexture("resources/textures/default.png");

			//this->model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = LoadTexture("resources/textures/Block/Brick/brick_SPEC.png");
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
}
