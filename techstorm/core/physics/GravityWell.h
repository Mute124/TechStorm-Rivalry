#pragma once
#include <raylib.h>
#include "Velocity.h"
#include <vector>
#include <map>
#include "../registry/Registry.h"

class GravityWells;

Vector3 CalculateWellPower(Vector3 center, double gravIntensity, double mass) {
	return Vector3AddValue(center, (gravIntensity * mass));
}

// an object with gravitational influence.
class GravityWell : public GameObject {
public:
	double gravIntensity; // how powerful this gravity well is.
	double mass; // How big the gravity well is, Remember, it can be powerful but small.
	Vector3 center; // center of mass!
	Vector3 wellPower;
	unsigned int id; // it's id.

	GravityWell() {
		this->threadSafe = true;
		this->isDynamic = true;
		this->gravIntensity = 1.0f;
		this->mass = 8.0f;
		this->position = Vector3One();
		this->center = position;
	}

	GravityWell(int a) {
		this->threadSafe = true;
		this->isDynamic = true;
		this->gravIntensity = 1.0f;
		this->mass = 8.0f;
		this->position = Vector3{ 5, 5, 5 };
		this->center = position;
	}

	void draw() override {
		DrawSphere(this->position, 0.5f, RED);
	}

	void onUpdate() override {
	}

	void onDestroy() const override {
		delete this;
	}
};

class GravityWells {
public:
	static inline std::map<int, GravityWell*> gravWells;
	static inline int count = 0;

	void tester() {
		push(new GravityWell());
	}

	void ndTester() {
		push(new GravityWell(1));
	}

	void push(GravityWell* well) {
		well->id = count;
		gravWells[count] = well;
		count++;
	}
};
