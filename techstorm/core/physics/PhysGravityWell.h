#pragma once
#include "GravityWell.h"
#include "PhysProperty.h"
#include "../../Common.h"

class PhysGravityWell : public PhysProperty, public GravityWell {
public:

	virtual void update() override {
	}
};
