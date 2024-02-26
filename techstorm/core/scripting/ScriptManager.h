#pragma once
#define MAX_SCRIPTABLES 100

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>

#include "IScriptable.h"
#include "../registry/Registry.h"
#include "../threading/ThreadGroups.h"
#include "../threading/ThreadGroupTask.h"


// Class that manages scripting and calls the script functions
// todo: make this thread safe, and run in a threadgroup.
class ScriptManager : public MRegistry<IScriptable> {
public:

	static void init() {}

	void start(bool threaded = false) {

		_isThreaded = threaded;
		for (int i = 0; i < _scripts.size(); i++) {
			_scripts[i]->init();

			_scripts[i]->update();
		}



		if (_isThreaded) {
			
#ifdef USE_PROTOTYPE_THREADING
			ThreadGroups::_threadGroups["scripting"]->addTask(std::make_unique<ThreadGroupTask>(std::move(std::bind(&ScriptManager::beginLoop, this))));
#else
			ThreadGroups::push("scripting", ThreadGroupTask::MakeThreadGroupTask(std::bind(&ScriptManager::beginLoop, this)));
#endif
		}


	}



	// Override function
	void updateObjects() {
		for (int i = 0; i < _scripts.size(); i++) {
			_scripts[i]->update();
		}
	}

	static inline void addScript(IScriptable* script) {
		_scripts[getID()] = script;
	}

	void removeScript(int ID) {
		getItem(ID)->end();
		Remove(ID);

		// remove from map
		_scripts.erase(ID);
	}
	
	void end() {
		for (int i = 0; i < _scripts.size(); i++) {
			_scripts[i]->end();
		}
	}

private:

	void beginLoop() {
		this->updateObjects();
	}

	static inline int _count = 0;

	// NOTE: Use only if you are pushing into the map!
	static int getID() {
		return _count;
		_count++;
	}

	static inline bool _isThreaded = false;

	static inline std::map<int, IScriptable*> _scripts;
};