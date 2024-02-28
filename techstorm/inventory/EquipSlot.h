/*
* Here is how the EquipSlot works. at the bottom of the screen the primary, secondary, and melee slots will be shown. Only certain weapons can be within each slot. Secondary weapons are more like pistols, smgs, etc.
* Primary weapons are things like Rifles, Shotguns, etc.
*
*
*/

#pragma once

#include "raylib.h"

struct EquipSlot {
	const int slotIndex;
};
