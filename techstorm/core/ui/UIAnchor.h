#pragma once
#include "../../Common.h"

class UIAnchor {
public:
	Vector2 position;
	bool isLocked;
	bool positionDirty;

	void lock() {
		this->isLocked = true;
	}

	void unlock() {
		this->isLocked = false;
	}

	void moveTo(Vector2 dst) {
		this->position = dst;
		this->positionDirty = true;
	}

	void setCleaned() {
		this->positionDirty = false;
	}
};
