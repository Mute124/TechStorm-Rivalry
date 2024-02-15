#pragma once
#include "Common.h"
#include "ESeverity.h"
#include "AfflictionAffect.h"
#include "Item.h"

#define MAX_TREATMENTS 100
class Affliction {
public:

	Affliction(const char* name, const char *tooltip, const char* discription, const char *iconPath, const int implication, ESeverity severity, AfflictionAffect affect)
		: name(name), description(discription), toolTip(tooltip), icon(LoadImage(iconPath)), implication(implication), severity(severity), affect(affect)
	{

	}

	~Affliction() {
		delete id;
		delete[] Treatments;
		delete this;
	}
	const char* name;
	const char* description;
	const char* toolTip;
	const Image icon;
	const int implication;

	int* id;

	const ESeverity severity;

	// TODO: Add cause variable

	// TODO: fix   \/
	Item* Treatments[MAX_TREATMENTS];

	const AfflictionAffect affect;
};