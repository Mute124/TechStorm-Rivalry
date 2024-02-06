#pragma once
#include "EEquipSlotTypes.h"
#include "EEquipmentTypes.h"
#include "EAfflictions.h"

// Character Weapon
struct CWeapon {
	EEquipmentTypes weaponType;
	EEquipmentSlots weaponSlot;

	// final damage is based on range, hit location, falloff, and a random number between these values
	int dmgLow;
	int dmgHigh;

	// how much damage is reduced by the fall off
	int dmgFallOff;

	// Keep watch on this, check to see if it can stay as a 16 bit integer or if it needs to be at least 32 bit. I think it can stay as a 16 bit integer
	int range;

	// How much the bullet drops when fired. Laser weaponry is not affected by this!
	double bulletDrop;

	const char* NAME;

	// What it can give to the player when they get shot. Example of which is kinetic guns tend to make you bleed!
	EAfflictions possibleAfflictions[];
	

};
