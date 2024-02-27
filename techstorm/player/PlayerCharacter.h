#pragma once
#include "../core/ecs/ECSMan.h"
#include "../character/Character.h"
#include "../core/input/InputComponent.h"
#include "PlayerComponent.h"
#include "CameraComp.h"
#include "HealthBar.h"

class PlayerCharacter : public Character, public PlayerController, public CameraComp { 
public:
	void onDestroy() const override
	{
		delete this;
	};

	void onUpdate() override
	{
		//this->setSpeed(this->speed);
		if (cameraMode != CAMERA_FIRST_PERSON) {
			if (this->doDraw) {
				DrawModel(model, this->getPosition(), 0.2f, GREEN);
			}
		}

		
		this->setSpeed(this->speed);

		updateController(getSelfCameraPointer());
		//PrintFloat("speed", this->speed);
		//PrintFloat("PlayerSpeed", this->movementSpeed);
		//PrintFloat("affectDelta", this->speedAffectDelta);
		//PrintFloat("baseSpeed", this->baseSpeed);
		
		
		// View Sway
		// Sway timer is equal to swayTimer + frame delta time
		swayTimer += GetFrameTime();
		this->setTarget(Vector3{ this->setTarget().x + sin(swayTimer * swaySpeed) * swayAmount, this->setTarget().y, this->setTarget().z + cos(swayTimer * swaySpeed) * swayAmount });



	};
	// sends player data to the games render
	void draw() override
	{
	}

	int cameraMode;

	bool doDraw = false;

	HealthBar* healthBar;
	// Viewsway
	float swayAmount = 0.0003f;
	float swaySpeed = 0.02f;
	float swayTimer = 0.0f;
};