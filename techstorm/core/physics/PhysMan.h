#pragma once
#include "ObjectCollider.h"
#include "GravityWell.h"
#include "PhysObject.h"

static std::map<int, GravityWell*> gravWells;
static int wellCount = 0;

// calculates influence
Vector3 computeWellPull(PhysObject* obj) {
	for (auto& well : gravWells) {
		well.second->wellPower = Vector3AddValue(well.second->center, (well.second->gravIntensity * well.second->mass));
	}
}
