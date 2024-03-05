#pragma once
#include "Velocity.h"

// adds acceleration
AngularVelocity AngularVelocityAdd(AngularVelocity vel, AngularAcceleration acc) {
	vel.pitch += acc.pitch;
	vel.roll += acc.roll;
	vel.yaw += acc.yaw;

	return vel;
}

Vector3 AngularVelocityToVector3(AngularVelocity vel) {
	Vector3 vec3 = { vel.pitch, vel.yaw, vel.roll };
	return vec3;
}

Matrix AngularVelocityToMatrix(Matrix mat, AngularVelocity vel) {
	return MatrixRotateXYZ(vel);
}

Matrix MatrixAddAngularAcceleration(Matrix mat, AngularAcceleration acc, AngularVelocity vel) {
	return MatrixRotateXYZ(AngularVelocityToVector3(AngularVelocityAdd(vel, acc)));
}

Velocity UpdateVelocity(Velocity vel) {
	vel.angVel = AngularVelocityAdd(vel.angVel, vel.angAcc);
	vel.vVel = Vector3Add(vel.vVel, vel.vAcc);

	return vel;
}
