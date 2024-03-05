#pragma once
#include <raylib.h>
#include "Velocity.h"
#include <vector>
#include <map>
#include "../registry/Registry.h"

class GravityWells;
class GravityWell {
public:
	double gravitationalAttraction; // how powerful this gravity well is.
	double mass; // How big the gravity well is, Remember, it can be powerful but small.
	Vector3D position; // where the gravity well is.
	double acceleration;
	unsigned int id; // it's id. duh
};

class GravityWells : public MRegistry<GravityWell*> {
public:
};
