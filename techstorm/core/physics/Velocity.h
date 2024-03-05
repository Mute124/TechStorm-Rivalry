#pragma once
#include <raylib.h>
#include <raymath.h>
#include "Vector3D.h"

// per tick
typedef struct AngularVelocity {
	double yaw; // y axis
	double pitch; // x axis
	double roll; // z axis
} AngularVelocity;

typedef struct AngularVelocity AngularAcceleration;

/*
* vVel is the direction
* vAcc is the directional acceleration.
* angVel is the angular direction
* andAcc is the angular acceleration.
*
*/
typedef struct Velocity {
	Vector3 vel;
	Vector3 acc;
	double momentum;
	double speed;
} Velocity;

//extern Vector3 AngularVelocityToVector3(AngularVelocity vel);

//extern Matrix AngularVelocityToMatrix(Matrix mat, AngularVelocity vel);

//extern Matrix MatrixAddAngularAcceleration(Matrix mat, AngularAcceleration acc, AngularVelocity vel);

//extern Velocity UpdateVelocity(Velocity vel);
