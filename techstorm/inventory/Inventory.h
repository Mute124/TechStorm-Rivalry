#pragma once
#include "common.h"
#include "Item.h"
#include "Data/gui/styles/techstorm-theme.h"

class InventoryGUI {
public:

	InventoryGUI(std::map<const char*, Item*> items, std::vector<Item*> itemsVector) {
		this->itemsMap = items;
		this->itemsRegistry = itemsVector;
	}

	void draw() {
	}

	std::map<const char*, Item*> itemsMap;
	std::vector<Item*> itemsRegistry;
};
