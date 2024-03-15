#pragma once
#include "../../Game.h"
#include "../../Common.h"
#include "Velocity.h"
#include "GravityWell.h"

class PhysObject : public GameObject {
public:

	double envResistance = 0.04; // how much resistance is in the env
	Vector3 pull = Vector3One();
	double mass = 3.0f; // in kg
	Energy energyConstant;
	Energy specificPotentialEnergy;
	Energy specificKineticEnergy;
	Energy specificOrbitalEnergy;
	double momentum;
	double avgVelocity;
	double tangientalVelocity;

	Velocity vel;
	Quaternion rot;
	Vector3 prevAcc;

	PhysObject() {
	}

	PhysObject(Shader shdr, Vector3 pos) {
		this->init(shdr, pos);
	}

	void init(Shader shdr, Vector3 pos) {
		this->threadSafe = true;
		this->isDynamic = true;
		this->position = pos;

		this->model = GetDefaultModel();
		this->tint = WHITE;
		this->shdr = shdr;
		const static Texture2D Bricks = LoadTexture("resources/textures/Block/Brick/Brick.png");
		this->model.materials[0].shader = this->shdr;

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
		this->precompute();
	}

	void init(Shader shdr) {
		this->threadSafe = true;
		this->isDynamic = true;
		this->position = Vector3{ 10, 10, 10 };

		this->model = GetDefaultModel();
		this->tint = WHITE;
		this->shdr = shdr;
		const static Texture2D Bricks = LoadTexture("resources/textures/Block/Brick/Brick.png");
		this->model.materials[0].shader = this->shdr;

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
		this->precompute();
	}

	virtual void draw() override {
		this->model.transform = QuaternionToMatrix(rot);
		DrawModel(this->model, this->position, 1.0f, WHITE);

		//DrawLine3D(this->position, Vector3Add(this->vel.vel, this->position), WHITE);
		//DrawSphere(Vector3Add(this->vel.vel, this->position), 0.2f, RED);
	}

	virtual void onUpdate() override {
		double wellPull;

		for (int i = 0; i < GravityWells::count; i++) {
			GravityWell* well = GravityWells::gravWells.at(i);

			double dst = Vector3Distance(well->position, this->position);

			double power = (well->gravIntensity * well->mass / pow(dst, 2.0f) * this->mass) * envResistance;

			Vector3 wellPos = well->position;

			this->specificPotentialEnergy;

			this->vel.acc = Vector3AddValue(Vector3Add(this->vel.vel, Vector3Subtract(this->vel.acc, this->prevAcc)), power);
			this->vel.vel = Vector3Lerp(wellPos, this->position, dst * GetFrameTime());

			this->position = Vector3Lerp(this->position, this->vel.vel, -power * GetFrameTime());

			rot = QuaternionFromVector3ToVector3(this->position, Vector3AddValue(wellPos, power));

			float x = this->vel.vel.x * this->mass;
			float y = this->vel.vel.y * this->mass;
			float z = this->vel.vel.z * this->mass;

			this->vel.momentum = x + y + z;

			this->prevAcc = this->vel.acc;
			this->vel.acc = Vector3SubtractValue(this->vel.vel, this->envResistance);
			this->avgVelocity = Vector3Avg(this->vel.vel);

			this->tangientalVelocity = (Vector3Angle(this->position, wellPos) / 2.0f) * dst;

			this->vel.vel.z = this->vel.vel.z + this->tangientalVelocity;
			this->vel.vel = Vector3AddValue(this->vel.vel, this->avgVelocity + this->vel.momentum + this->tangientalVelocity);

			//this->prevAcc = this->vel.acc;
			//this->vel.acc = Vector3Zero();
			//Vector3 WellPowerV = Vector3AddValue(well->center, (well->gravIntensity * well->mass));
			//Logman::Log(TextFormat("[%i] Intensity : %f, Mass : %f,  pos : %f, %f, %f : well : %f, %f, %f : dst : %f : power : %f", i, well->gravIntensity, well->mass, (float)position.x, (float)this->position.y, this->position.z, well->position.x, well->position.y, well->position.z, dst, power));
			//wellPull = Vector3Distance(well->position, this->position);

			//pull = Vector3Subtract(pull, Vector3Subtract(WellPowerV, Vector3{ (float)this->vel.momentum * this->position.x + (float)wellPull, (float)this->vel.momentum * this->position.y + (float)wellPull, (float)this->vel.momentum * this->position.z + (float)wellPull }));
			//Logman::Log(TextFormat("Well Power : %f, %f, %f : Well pull : %f : total Pull : %f, %f, %f : Momentum : %f", WellPowerV.x, WellPowerV.y, WellPowerV.z, wellPull, this->pull.x, pull.y, pull.z, this->vel.momentum));
		}

		//Logman::Log(TextFormat("position : %f, %f, %f", position.x, position.y, position.z));
	}

	void onDestroy() const override {
		delete this;
	}

private:

	void precompute() {
		this->energyConstant = this->mass * pow(LIGHT_SPEED, 2);

		float x = this->vel.vel.x * this->mass;
		float y = this->vel.vel.y * this->mass;
		float z = this->vel.vel.z * this->mass;

		this->vel.momentum = x + y + z;

		this->avgVelocity = Vector3Avg(this->vel.vel);
	}
};