#pragma once
#include "ScriptManager.h"

class IScriptable abstract {
public:

	IScriptable() {
	}

	virtual void init();
	virtual void update();
	virtual void end();

	int ID;
};
