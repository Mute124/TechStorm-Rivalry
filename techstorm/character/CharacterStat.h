#pragma once
#include "../Common.h"
#include "../core/logging/Logman.h"
/*
* Classifications are based off of real wound classifications. Green (minor), yellow(moderate), and red(critical)
*
* Minor severity denotes it is in early stage of healing, and most likely to recover with adequate care
*
* Moderate severity denotes it should get more medical attention and treatment than minor ones, but is unlikely to become lethal.
*
* Critical severity denotes it NEEDS medical attention
*
*/
enum EStatSeverity {
	SEVERITY_NULL,
	SEVERITY_MINOR,
	SEVERITY_MODERATE,
	SEVERITY_CRITICAL
};

/*
* Note:
*	Make stats are NORMALIZED, and they are on a range of 0.0f to 100.0f, and should not go above.
*	Also All deltas are to the HUNDRETHS PLACE, Meaning, 0.03 will be a 3% change over time, and 0.3 is 30% change in time! This gets calculated EACH TICK.
*
*	Formula for caculating the stat:
*		S = severityDelta
*		s = Scaling factor
*		y = Final value
*		x = current value
*		c = delta value.
*
*		y = s * (  x * c   )
*			----------------
*				  S
*
*		This calculates only the change. Add it onto the current value to add it's affect. You can alternatively use x as the previous delta, to increment the delta.
*
*	Usecase :
*		Look in Affliction.h for this entry.
*/
class CharacterStat {
public:
	float val; //
	float deltaVal; // change in time
	const char* name;
	bool isBad;

	bool isAffliction;
	bool isTrait;

	// Set isBad to true if it should start AT ZERO
	CharacterStat(bool isBad, const char* name, float delta) : name(name) {
		if (!isBad) {
			this->val = 100.0f;
		}
		else {
			this->val = 0.0f;
		}

		this->deltaVal = delta;
	}

	// Set isBad to true if it should start AT ZERO.
	CharacterStat(bool isBad, const char* name) : name(name) {
		if (!isBad) {
			this->val = 100.0f;
		}
		else {
			this->val = 0.0f;
		}

		this->deltaVal = 0.0f;
	}

	CharacterStat() {
	}

	// adds the changeVal parameter to the deltaVal
	void changeDelta(float delta) {
		this->previousDelta = this->deltaVal;
		this->deltaVal += delta;
	}

	// calculate this stat's new state.
	void tick() {
		/*
		* incremental delta is calculated based on the slope of the previous and current delta times treatmentDelta + the stat's base severity delta.
		* equation looks like below
		*
		* idelta = tDelta(pDelta - cDelta) + bSeverity
		*
		*
		*/
		this->previousDelta = this->deltaVal;
		this->deltaVal += (incrementalDelta - treatmentDelta) * severityDelta;

		this->val += (deltaVal - treatmentDelta) * severityDelta;

		this->val = Clamp(this->val, 0.0f, 100.0f);

		onTick();

		Logman::Log(TextFormat("Delta : %f, Val : %f, tDelta : %f", deltaVal, val, treatmentDelta));
	}

	// override this in the event you want extra behaviors in the stat.
	virtual void onTick() {
	}

	void getImpact(float health) {
	}

protected:
	// used to calculate incremental severity
	float previousDelta;
	float severityDelta = 0.04f;

	float treatmentDelta;
	float incrementalDelta = 0.003f;
};
