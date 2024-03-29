#pragma once
#include <tinyxml2.h>
#include "Logman.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "Item.h"

#define _NO_CRT_STDIO_INLINE

using namespace tinyxml2;

class InventoryMan {
public:
	InventoryMan(const char* itemsFilePath) : ITEMSPATH(itemsFilePath) {
	}

	// Essentially loads and sets up all items within resources.tsr file.
	// .tsr file stands for TechStorm Resources.
	static inline void SetupItems() {
		XMLDocument doc;
		doc.LoadFile("data/Items/resources.tsr");

		XMLElement* itemsRoot = doc.RootElement();

		Item* item = { 0 };
		int mapSize = 0;
		if (NULL != itemsRoot) {
			XMLElement* itemElements = itemsRoot->FirstChildElement("Items");

			if (NULL != itemElements) {
				XMLElement* itemElement = itemElements->FirstChildElement("Item");

				while (itemElement) {

					// Item setup code

					// Todo : Make this fully autonomous
					XMLElement* itemName = itemElement->FirstChildElement("Name");

					//Logman::Log(itemName->GetText());

					XMLElement* materialType = itemElement->FirstChildElement("MaterialType");

					XMLElement* icon = itemElement->FirstChildElement("Icon");

					XMLElement* rarity = itemElement->FirstChildElement("Rarity");

					// todo : Assign IDs
					item = new Item(itemName->GetText(), materialType->GetText(), LoadImage(icon->GetText()), NULL, rarity->GetText());

					mapSize = Register(item);
					itemElement = itemElement->NextSiblingElement("Item");
				}
			}
		}

		for (auto& obj : simpleItemRegistry)
		{
			obj->log();
		}
	}

	static inline std::map<const char*, Item*> itemMap;
	static inline std::vector<Item*> simpleItemRegistry;

	static inline int itemCount = 0;

private:

	const char* ITEMSPATH;

	static inline int Register(Item* item) {
		itemMap[item->NAME] = item;

		int mapSize = static_cast<const int>(itemMap.size());
		itemMap[item->NAME]->ID = &mapSize;

		simpleItemRegistry.push_back(item);
		itemCount = mapSize;
		return mapSize;
	}
};
