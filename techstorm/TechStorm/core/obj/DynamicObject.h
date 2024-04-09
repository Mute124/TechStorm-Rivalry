#pragma once
#include "../../Common.h"
#include "../physics/RigidBody.h"

// A game object that is constantly updated.
class DynamicObject abstract : public GameObject {
public:

	void init() {
		this->isDynamic = true;
	}
};
