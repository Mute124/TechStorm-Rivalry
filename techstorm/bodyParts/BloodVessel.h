#pragma once
#include "EBloodVesselClassification.h"
#include "Blood.h"

class BloodVessel abstract {
public:
	unsigned int vesselID;
	const char* name;
	Blood* vesselBlood;
	EBloodVesselClassification eVesselClassification;
	float vesselDilation; // 0 = vasoconstriction, 1 = vasodilation
	float vesselSize; // this affects how likely it is to get hit
	float vesselProtection; // how much of that meaty flesh protects the blood vessel. 0 = surface level, 1 = deep, runs along the bone
};
