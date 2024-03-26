#pragma once
#include "../input/Keybind.h"
#include "../registry/Registry.h"

class Controller : public MRegistry_Ext<KeyboardKey, Keybind*> {
public:
	float mouseSensitivity = 0.05f;

	void update() {
	}
};
