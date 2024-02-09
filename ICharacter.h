#pragma once
#include "EBodySlots.h"
#include "BodySlot.h"
#include "IScriptable.h"
#include "ScriptManager.h"
#include "EFaction.h"


// A game character, define the scriptable functions in your implementation!
class ICharacter : public IScriptable
{
	ICharacter(int characterID, bool isPlayer, EFaction faction) : characterID(characterID), isPlayer(isPlayer), characterFaction(faction) {

	}

	EBodySlots bodySlots;
	BodySlot* bodySlot[SLOT_COUNT] = { 0 };

	bool isDead;
	bool isCrouched;
	bool isRunning;
	bool isSprinting;
	const bool isPlayer;

	const int characterID;
	const EFaction characterFaction = FACTION_NULL;

	

public:
};

