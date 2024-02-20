#pragma once
#include "Common.h"
#include "GameObject.h"

class CelestialBody : public GameObject
{

public:
	CelestialBody() {
	
	}
	~CelestialBody() {}
	
	Vector3 bodyPosition;
	Model model;
};

