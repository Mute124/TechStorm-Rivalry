#pragma once
#include "../../Game.h"
#include "../../Common.h"
#include "Velocity.h"
#include "GravityWell.h"
#include "PhysicsConstants.h"

class PhysObject : public GameObject {
public:
	double envResistance = 0.04; // how much resistance is in the env
	Vector3 pull = Vector3One();
	float mass = 3.0f; // in kg
	Energy energyConstant;
	Energy specificPotentialEnergy;
	Energy specificKineticEnergy;
	Energy specificOrbitalEnergy;
	Force impactForce; // in newtons.
	double tangientalVelocity;
	double scalarMomentum;
	float scalarSpeed;
	float averageVelocity;
	float scalarAcceleration;
	Vector3 linearVelocity;
	Vector3 linearSpeed;
	Vector3 linearAcceleration;
	Vector3 prevLinearAcceleration;
	Vector3 prevLinearVelocity;
	Quaternion rot;
	GravityWell* selfWell;

	PhysObject() {
	}

	PhysObject(Shader shdr, Vector3 pos) {
		this->selfWell = new GravityWell();
		this->selfWell->gravIntensity = 1.5f;
		GravityWells::push(this->selfWell);
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
		this->selfWell = new GravityWell();
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

		DrawLine3D(this->position, this->linearVelocity, YELLOW);
		DrawSphere(this->linearVelocity, 0.2f, YELLOW);

		DrawLine3D(this->position, this->linearAcceleration, RED);
		DrawSphere(this->linearAcceleration, 0.2f, RED);
	}

	virtual void onUpdate() override {
		double wellPull;
		Vector3 preCalculationPosition = this->position;
		for (int i = 0; i < GravityWells::count; i++) {
			GravityWell* well = GravityWells::gravWells.at(i);

			Vector3 wellPos = well->position;

			double dst = Vector3Distance(wellPos, this->position);
			double force = GRAVITATIONAL_CONSTANT * ((well->mass * this->mass) / powf(dst, 2));

			// a = dV / dT
			this->scalarAcceleration = Vector3Distance(this->linearVelocity, this->prevLinearVelocity) / GetFrameTime();

			this->impactForce = this->mass * this->scalarAcceleration;

			//Vector3 pullByGravity = Vector3Lerp(this->position, wellPos, )

				// average velocity is equal to speed divided by time, we are using frame time as it is a good representation of time passed.
			this->averageVelocity = scalarSpeed / GetFrameTime();

			//this->linearVelocity = Vector3Distance(this->position, );

			// k = 1/2 * m * v^2
			this->specificKineticEnergy = 0.5 * this->mass * pow(this->averageVelocity, 2);

			// the rest of the energy is potential energy.
			this->specificPotentialEnergy = abs(this->specificKineticEnergy - this->energyConstant);

			this->prevLinearVelocity = this->linearVelocity;
			/*
			* this->specificKineticEnergy = 0.5 * this->mass;

			this->linearAcceleration = Vector3AddValue(Vector3Add(this->linearVelocity, Vector3Subtract(this->linearAcceleration, this->prevLinearAcceleration)), -power);
			this->linearVelocity = Vector3Lerp(wellPos, this->position, dst * GetFrameTime());

			this->position = Vector3Lerp(this->position, this->linearVelocity, power * GetFrameTime());

			rot = QuaternionFromVector3ToVector3(this->position, Vector3AddValue(wellPos, power));

			float x = this->linearVelocity.x * this->mass;
			float y = this->linearVelocity.y * this->mass;
			float z = this->linearVelocity.z * this->mass;

			this->scalarMomentum = x + y + z;

			this->prevLinearAcceleration = this->linearVelocity;
			this->linearAcceleration = Vector3SubtractValue(this->linearVelocity, this->envResistance);

			this->tangientalVelocity = (Vector3Angle(this->position, wellPos) / 2.0f) * dst;

			this->linearVelocity.z = this->linearVelocity.z + this->tangientalVelocity;
			this->linearVelocity = Vector3AddValue(this->linearVelocity, this->scalarMomentum + this->tangientalVelocity);
			*/
		}

		this->scalarSpeed = CalculateVector3Speed(preCalculationPosition, this->position);

		// calculate impact force.
	}

	void onDestroy() const override {
		delete this;
	}

private:

	// precompute constants.
	void precompute() {
		this->energyConstant = this->mass * pow(LIGHT_SPEED, 2);

		float x = this->linearVelocity.x * this->mass;
		float y = this->linearVelocity.y * this->mass;
		float z = this->linearVelocity.z * this->mass;

		this->scalarMomentum = x + y + z;
	}
};
