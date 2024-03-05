#pragma once
#include "Gameobject.h"

#define DEFAULT_INTERACTION_KEY KeyboardKey::KEY_E

class InteractiveObject abstract : public GameObject {
public:
	void interact() {
		onInteraction();
	}
protected:
	bool playerInteracting = false;
	bool drawToolTip = false;
	int shouldDrawDistance; // how far the player needs to be to see the tooltip.

	void onUpdate() override {
	}

	virtual void onObjectUpdate() {
	}

	virtual void onInteraction() {}
};
