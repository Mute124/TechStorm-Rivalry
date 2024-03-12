#pragma once
#include "../core/obj/Gameobject.h"
class Terrain : public GameObject {
public:
	Terrain() {
	}

	virtual void onDestroy() const override {
		delete this;
	}
};
