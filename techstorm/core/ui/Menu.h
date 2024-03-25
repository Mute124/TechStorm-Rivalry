#pragma once
#include "UIMan.h"
#include "../utils/Button.h"
#include "../gamescreen/MenuCamera.h"

// just a modified UI container
class Menu : UIContainer {
public:
	void constructMenu(bool awakeOnPush);
	virtual void initMenu();
	virtual void tickMenu();
};
