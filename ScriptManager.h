#pragma once
#define MAX_SCRIPTABLES 100

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "IScriptable.h"
#include "Registry.h"

// Class that manages scripting and calls the script functions
// Todo : make this load script files and run them, also make it have a script cap.
class ScriptManager : public MapRegistry<IScriptable> {
public:


	void start() {
	
	}

	// Override function
	void Update() override {

	}



	void AddScript(IScriptable* script) {
		Add(script);
	}

	void RemoveScript(int ID) {
		Get(ID)->onEnd();
		Remove(ID);
	}



};