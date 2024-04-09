#pragma once
#include "../obj/gameObject.h"
#include "../../Game.h"

namespace Primatives {
	class Sphere : public GameObject {
	public:
		float radius;
		int slices;
		int rings;

		Sphere(Vector3 pos, float radius, int slices = 16, int rings = 16) {
			this->position = pos;
			this->radius = radius;
			this->shdr = Game::renderers->forwardRenderer->pbrShader;
			this->model = LoadModelFromMesh(GenMeshSphere(this->radius, this->rings, this->slices));

			this.model.materialCount = 1;

			this->model.materials[0].shader = this->shdr;
			this->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = GetDefaultTexture();
		}

		void draw() override {
			DrawModel(this->model, this->position, 1.0f, WHITE);
		}
		void onDestroy() const override {
			delete this;
		}
	};

	void SpawnSphere(Vector3 pos, float radius, int slices = 16, int rings = 16) {
		Game::objMan->pushObject(new Sphere(pos, radius, slices, rings));
	}
}
