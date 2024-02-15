#pragma once
#include "Common.h"
#include "EBodySlots.h"
#include "BodySlot.h"
#include "IScriptable.h"
#include "ScriptManager.h"
#include "EFaction.h"


// A game character abstract class
class Character 
{
public:
	Character(int characterID, bool isPlayer, EFaction faction) : characterID(characterID), isPlayer(isPlayer), characterFaction(faction) {

	}

	EBodySlots bodySlots;
	BodySlot* bodySlot[SLOT_COUNT] = { 0 };

	bool isDead;
	bool isCrouched;
	bool isRunning;
	bool isSprinting;
	const bool isPlayer;

	Ray characterLookDirection = { 0 };

	const int characterID;

	const EFaction characterFaction = FACTION_NULL;

	Model characterModel;
	Vector3 characterPosition;

};

