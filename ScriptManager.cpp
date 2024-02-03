#include "ScriptManager.h"

// todo : make this load script files and run them
void ScriptManager::start() {

}

void ScriptManager::update() {
	for (auto& script : scriptables) {
		script->onUpdate();
	}
}

void ScriptManager::Flush() {
	for (auto& script : scriptables) {
		script->onEnd();
	}

	scriptables.clear();
}

void ScriptManager::AddScript(Scriptable* script) {
	scriptables.push_back(script);

	script->onStart();
}