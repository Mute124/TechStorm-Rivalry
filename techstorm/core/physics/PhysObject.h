#pragma once
#include "../../Common.h"
#include "Velocity.h"

class PhysObject : public GameObject {
protected:
	Vector3D gravityInfluence;
	double mass;
	Velocity vel;
	AngularVelocity angVel;
	AngularAcceleration angAcc;
};
