#pragma once
#define MAX_SCRIPTABLES 100

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "IScriptable.h"


using namespace std;

// Class that manages scripting and calls the script functions
// Todo : make this load script files and run them, also make it have a script cap.
class ScriptManager {
public:


	void start();

	void update();

	void Flush();

	void AddScript(IScriptable* script);
	vector<IScriptable*> scriptables;
};