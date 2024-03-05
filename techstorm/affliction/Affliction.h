#pragma once
#include "../character/CharacterStat.h"
#include "../core/ui/UIMan.h"

/*
* Afflictions, traits, and stats, whats the difference? It is all about the persistance of it. Keep in mind that they are not always a bad thing to have but ussually are.
*
* Affliction :
*	Something that can be given and removed, and is only short term, for example bleeding is a affliction. These can be treated and are acute in nature.
*
* Trait :
*	A modified version of a affliction that can be given, but is HARD or damn near impossible to remove. Think of it as chronic. Example of which includes brain damage.
*	Traits also can fundamentally change the play style of the player.
*
* Stat :
*	This is something that the character WILL ALWAYS have, it cannot be given nor taken, this is a static constant. Examples of which is happiness. These also are the highest impact
*	to the character's health
*
*
* Please inherit from this class to create other afflictions or it will simply by a null affliction!
*/
class AfflictionBase abstract : public CharacterStat {
protected:

	bool isTreated;
	float treatmentDelta;

	void init(const char* name, bool isBad, float startDelta = 0.0f) {
		this->isBad = isBad;
		CharacterStat(isBad, name, startDelta);
	}

	// Note: THE DELTA MUST BE POSITIVE!
	void treat(float delta) {
		this->isTreated = true;
		this->treatmentDelta = -delta;
		onTreat();
	}

	// Override to add custom functionality.
	virtual void onTreat() {
	}
};
