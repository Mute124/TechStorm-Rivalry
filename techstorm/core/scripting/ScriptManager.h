#pragma once
#define MAX_SCRIPTABLES 100

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "IScriptable.h"
#include "../registry/Registry.h"

// Class that manages scripting and calls the script functions
// Todo : make this load script files and run them, also make it have a script cap.
class ScriptManager : public MRegistry<IScriptable> {
public:


	void start() {
	
	}

	// Override function
	void updateObjects() override {

	}



	void addScript(IScriptable* script) {
		Add(script);
	}

	void removeScript(int ID) {
		getConfig(ID)->onEnd();
		Remove(ID);
	}



};