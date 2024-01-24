#pragma once
#include "Common.h"
#include "ItemTypes.h"


typedef struct Item {

	void log() {
		Logman::Log(NAME);
	}

	Item(const char *name, const char *type, const Image icon, const int id) : NAME(name), TYPE(Translate(type)), ICON(&icon), ID(&id) {
		
	}
	const char* NAME; // Item Name
	const MaterialTypes* TYPE; // What type of item is this
	const Image* ICON; // Item icon
	const int* ID; // The id for this type of item.

	MaterialTypes *Translate(const char* target) {
		if (target == "Metal") {
			return new MaterialTypes(METAL);
		}
	}

};
