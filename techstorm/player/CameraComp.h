#pragma once
#include "../common.h"

class CameraData
{
public:
	Vector3 position; // Camera position
	Vector3 target;   // Camera target it looks-at
	Vector3 up;       // Camera up vector (rotation over its axis)
	float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
	int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

	Camera constructToCamera() {
		Camera camera = {
			position,
			target,
			up,
			fovy,
			projection
		};
		return camera;
	}
};

class CameraComp
{
public:
	CameraComp(CameraData cameradata) : camera(cameradata.constructToCamera()) {
	}

	CameraComp() {
	}

	Vector3 getPosition()
	{
		return this->camera.position;
	}

	Vector3 getTarget() {
		return this->camera.target;
	}

	Vector3 getUp()
	{
		return this->camera.up;
	}
	float getFOVY()
	{
		return this->camera.fovy;
	}

	int getProjection()
	{
		return this->camera.projection;
	}

	void getPosition(Vector3 value)
	{
		this->camera.position = value;
	}

	void setTarget(Vector3 value)
	{
		this->camera.target = value;
	}

	void setUp(Vector3 value)
	{
		this->camera.up = value;
	}

	void setFOVY(float value)
	{
		this->camera.fovy = value;
	}

	void setProject(int value)
	{
		this->camera.projection = value;
	}

	Camera toCamera(CameraData data) {
		return data.constructToCamera();
	}

	Camera getSelfCamera() {
		return this->camera;
	}

	Camera* getSelfCameraPointer() {
		return &this->camera;
	}

protected:

	Camera camera;
};
