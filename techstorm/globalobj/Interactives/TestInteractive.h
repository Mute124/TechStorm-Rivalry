#pragma once
#include "../../core/obj/InteractiveObject.h"

class TestInteractive : public TechStorm::InteractiveObject {
public:
	static void init() {
		br = LoadTexture("resources/textures/Block/Brick/Brick.png");
		GenTextureMipmaps(&br);
		mrao = LoadTexture("resources/textures/Block/Brick/brickMRAO.png");
		GenTextureMipmaps(&mrao);
		norm = LoadTexture("resources/textures/Block/Brick/brick_NORM.png");
		GenTextureMipmaps(&norm);
		hight = LoadTexture("resources/textures/Block/Brick/brick_DISP.png");
		GenTextureMipmaps(&hight);
		spec = LoadTexture("resources/textures/Block/Brick/brick_SPEC.png");
		GenTextureMipmaps(&spec);
	}

	static inline Texture2D br;
	static inline Texture2D mrao;
	static inline Texture2D norm;
	static inline Texture2D hight;
	static inline Texture2D spec;

	TestInteractive(Vector3 position, const Color color, Shader shader, Model model) {
		//Logman::customLog(LOG_TRACE, "Block Constructor", NULL);
		this->model = model;
		this->tint = color;
		this->position = position;
		this->shdr = shader;
		const static Texture2D Bricks = LoadTexture("resources/textures/Block/Brick/Brick.png");
		this->model.materials[0].shader = shader;

		// why the fuck does PBR lighting not work on AMD cards but not nvidia??
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.4f;
		this->model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.2f;
		this->model.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
		this->model.materials[0].maps[MATERIAL_MAP_EMISSION].color = Color{ 255, 162, 0, 100 };

		//		this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = Bricks;
		this->model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = mrao;
		this->model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = norm;
		this->model.materials[0].maps[MATERIAL_MAP_HEIGHT].texture = hight;
		this->model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = spec;
	}

	void draw() override {
		DrawModel(this->model, this->position, 1.0f, WHITE);
	}

	void onUpdate() override {
		SetShaderValue(this->shdr, GetShaderLocation(this->shdr, "position"), &this->position, SHADER_UNIFORM_VEC3);
	}

	static void setCam(Camera3D camera) {
		cam = cam;
	}

	void onDestroy() const override {
		delete this;
	}

protected:
	static inline Camera3D cam;
};
