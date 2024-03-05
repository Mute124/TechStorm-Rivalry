#pragma once
#include "UIMan.h"
#include "../utils/Button.h"
#include "../gamescreen/MenuCamera.h"

class Menu {
public:

protected:
	MenuCamera* camera;
	KeyboardKey trigger = KEY_NULL;
	bool isOpen;
	bool shouldExit;
	UIContainer* menuContainer;
};
