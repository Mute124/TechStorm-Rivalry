#pragma once
#include "InventoryManager.h"

class ICharacterHand
{
public:
	
	const char* equippedWeapon;

	void EquipWeapon(const char* weapon) {
		equippedWeapon = weapon;

		
	}
};

