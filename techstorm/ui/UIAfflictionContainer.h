#pragma once
#include "../core/ui/UIMan.h"
#include "UIAffliction.h"

class UIAfflictionContainer : public UIContainer {
public:

	Vector3 positions[4];

	void drawAffliction(UIAffliction* target) {
		this->addChild(target);
	}
};
