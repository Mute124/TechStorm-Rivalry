#pragma once
#include "../../Common.h"

class PlayerController
{
protected:

	int mode;
	float speed;
	float tiltSpeed;
	const float maxTiltRight = 10.0f; // Positive
	const float maxTiltLeft = -10.0f; // Negative
	float crouchSpeed;

	float screenTilt;

	float mouseSensitivity = 0.05f;

	KeyboardKey forward, backward, left, right, jump, crouch, tiltLeft, tiltRight;

	// needs to be optimized, technically we dont need parameters, we can just use this classes variable for it.
	float CalculateCameraTilt() {
		static const float NOCHANGE = 0.0f;

		return NOCHANGE;
	}
public:

	bool isRunning = false;
	bool canMove = true;
	bool isGrounded = false;


	float walkSpeed = 0.03f;
	float runChangeFactor = 43.33f;

	PlayerController(KeyboardKey Forward, KeyboardKey Backward, KeyboardKey Left, KeyboardKey Right, KeyboardKey Jump, KeyboardKey Crouch, int mode) : forward(Forward), backward(Backward), left(Left), right(Right), jump(Jump), crouch(Crouch), mode(mode)
	{
#ifndef tiltLeft
		tiltLeft = KEY_Q;
#endif // !tiltLeft
#ifndef tiltRight
		tiltRight = KEY_E;
#endif // !tiltRight
	}

	PlayerController() = default;

	void setSpeed(float speed) {
		this->speed = speed;
	}

	void update(Camera* camera)
	{

		if (!this->isRunning) {
			this->isRunning = false;
			setSpeed(this->walkSpeed); //m/s
		}
		else {
			this->isRunning = true;
			setSpeed(this->walkSpeed * runChangeFactor); //m/s
		}
		// Camera PRO usage example (EXPERIMENTAL)
		// This new camera function allows custom movement/rotation values to be directly provided
		// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
		UpdateCameraPro(camera,
			Vector3{
				(IsKeyDown(forward) || IsKeyDown(KEY_UP)) * speed -      // Move forward-backward
				(IsKeyDown(backward) || IsKeyDown(KEY_DOWN)) * speed,
				(IsKeyDown(right) || IsKeyDown(KEY_RIGHT)) * speed -   // Move right-left
				(IsKeyDown(left) || IsKeyDown(KEY_LEFT)) * speed,
				(IsKeyDown(jump)) * speed -                                                 // Move up-down
				(IsKeyDown(crouch)) * speed
			},
			Vector3{
				GetMouseDelta().x * mouseSensitivity,                            // Rotation: yaw
				GetMouseDelta().y * mouseSensitivity,                            // Rotation: pitch
				CalculateCameraTilt()                // Rotation: roll
			},

			GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)
	}
};