#pragma once
#include "common.h"
#include "Item.h"

class InventoryGUI {
public:

	InventoryGUI() {
	}

	static inline std::map<const char*, Item*> itemsMap;
	static inline std::vector<Item*> itemsRegistry;
};