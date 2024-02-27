#pragma once
#include "../character/Character.h"


class PlayerCharacter : public Character { 
public:
	void onDestroy() const override
	{
		delete this;
	};

	
	// sends player data to the games render
	void draw() override
	{
	}

	int cameraMode;

	bool doDraw = false;

	
	// Viewsway
	float swayAmount = 0.0003f;
	float swaySpeed = 0.02f;
	float swayTimer = 0.0f;
};