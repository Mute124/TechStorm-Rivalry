#pragma once
#include "Gameobject.h"

class StaticObject abstract : public GameObject {
public:

	void init(bool threadSafe) {
		this->threadSafe = threadSafe;
		this->isDynamic = false;
	}
};
