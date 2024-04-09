#pragma once
#include "../../Common.h"

struct Collision {
	GameObject* other;
	Vector3 where;
	float force; // in newtons
};
