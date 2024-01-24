#pragma once
#include <tinyxml2.h>
#include "Logman.h"

#define _NO_CRT_STDIO_INLINE

using namespace tinyxml2;

class InventoryMan {
public:
	InventoryMan(const char *itemsFilePath) {
		XMLDocument doc;
		doc.LoadFile(itemsFilePath);

		XMLElement* itemsRoot = doc.RootElement();

		if (NULL != itemsRoot) {
			XMLElement* itemElements = itemsRoot->FirstChildElement("Items");

			if (NULL != itemElements) {
				XMLElement *itemElement = itemElements->FirstChildElement("Item");

				while (itemElement) {
					// Item setup code
				}


			}
		}


	}
	
private:
	


};