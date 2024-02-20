#pragma once
#include "InventoryManager.h"

class ICharacterHand
{
public:
	
	const char* equippedWeapon;

	void equipWeapon(const char* weapon) {
		equippedWeapon = weapon;
	}
};

