#pragma once
#include "../Common.h"
#include "../core/input/Keybind.h"

// Obsolete, Use the one defined in Player.h instead!
class PlayerController
{
protected:

	int mode;
	float movementSpeed = 1.0f;
	float tiltSpeed;
	const float maxTiltRight = 10.0f; // Positive
	const float maxTiltLeft = -10.0f; // Negative
	float crouchSpeed;

	float screenTilt;

	float mouseSensitivity = 0.05f;

	// needs to be optimized, technically we dont need parameters, we can just use this classes variable for it.
	float CalculateCameraTilt() {
		static const float NOCHANGE = 0.0f;

		return NOCHANGE;
	}
public:

	float walkSpeed = 0.03f;
	float runChangeFactor = 43.33f;

	void updateStatus(float speed) {
		this->movementSpeed = speed;
	}

	PlayerController(int mode) : mode(mode)
	{
	}

	PlayerController() = default;

	void setSpeed(float speed) {
		this->movementSpeed = speed;
	}

	void updateController(Camera* camera)
	{
		// Camera PRO usage example (EXPERIMENTAL)
		// This new camera function allows custom movement/rotation values to be directly provided
		// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
		UpdateCameraPro(camera,
			Vector3{
				(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * movementSpeed -      // Move forward-backward
				(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * movementSpeed,
				(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * movementSpeed -   // Move right-left
				(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * movementSpeed,
				(IsKeyDown(KEY_SPACE)) * movementSpeed -                                                 // Move up-down
				(IsKeyDown(KEY_C)) * movementSpeed
			},
			Vector3{
				GetMouseDelta().x * mouseSensitivity,                            // Rotation: yaw
				GetMouseDelta().y * mouseSensitivity,                            // Rotation: pitch
				CalculateCameraTilt()                // Rotation: roll
			},

			GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)
	}
};
