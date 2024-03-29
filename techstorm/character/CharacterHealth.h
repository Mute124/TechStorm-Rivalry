/*
	Here is how a character's health is calculated.

	There are multiple factors, the main broad ones are bone health, circulatory health, brain health, critical organ health, risk factors (like weight),
	Immune health, skin health, etc.

	All of these are calculated in the same way.

	All of the character's bodily functions are the face value of how healthy that part is, this also affects the other parts, for example the circulatory system is
	paramount to the health of ALL parts.
*/
#pragma once
#include "IScriptable.h"

class CharacterHealth : public IScriptable {
public:

	CharacterHealth(double defaultBloodOxygenation, double defaultBloodVolume) {
	}

	int overallHealth;

	// blood
	double bloodOxygenation;
	double bloodVolume;
	double overallBloodPressure;

	// (the first and higher number) measures pressure inside your arteries when the heart beats.
	int systolicBloodPressure;

	// (the second and lower number) measures the pressure inside the artery when the heart rests between beats.
	int diastolicBloodPressure;

	int heartRate;

	bool isDead;

private:
	void calculateBloodPressure() {
		overallBloodPressure = systolicBloodPressure / diastolicBloodPressure;
	}

	void calculateOverallHealth() {
	}
};
