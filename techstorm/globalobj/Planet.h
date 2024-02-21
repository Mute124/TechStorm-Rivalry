#pragma once
#include "Common.h"
#include "CelestialBody.h"

class Planet : public CelestialBody
{
public:
	Planet() {
		
	}
	~Planet() {}

	void onUpdate() override {
	
	}
	void draw() override {

	}

	void onDestroy() const override {
		delete this;
	}
};