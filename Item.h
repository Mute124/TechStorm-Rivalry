/*
* Items should be put within the resources.tsr file!
*/
#pragma once
#include "Common.h"
#include "ItemTypes.h"

typedef struct Item {
	void log() {
		Logman::log(NAME);
	}

	// there are probably better ways to go about this, but I dont care right now 
	Item(const char* name, const char* type, const Image icon, const int id, const char *rarity) : NAME(name), TYPE(TranslateMaterialType(type)), ICON(&icon), ID(&id), RARITY(TranslateRarity(rarity)) {
		Logman::log(TextFormat("Item Created: %s, id of %i, rarity of %s", name, id, rarity));
	}

	~Item() {
		delete this;
	}

	const char* NAME; // Item Name
	const EMaterialTypes* TYPE; // What type of item is this
	const EItemRarity* RARITY;

	const Image* ICON; // Item icon
	const int* ID; // The id for this type of item.

	EMaterialTypes* TranslateMaterialType(const char* target) {
		if (target == "Metal") {
			return new EMaterialTypes(METAL);
		}
	}

	EItemRarity* TranslateRarity(const char* target) {
		if (target == "Common") {
			return new EItemRarity(COMMON);
		}
	}


};
