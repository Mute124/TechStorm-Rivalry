#pragma once
#include "../Common.h"
#include "../core/rendering/Renderer.h"

//#include "raylib-lua-sol.hpp"
#include <tuple>
#include <cassert>
#include <utility> // for std::pair

#include "../core/input/Cursor.h"

class LuaManager {
public:
	static inline sol::state lua; // Lua virtual machine
	static inline int modCount;

	LuaManager() {
	}

	void initLua() {
		startLua();
		loadMods();
	}

	void log(const char* b) {
		TechStorm::Logman::Log(b);
	}

	void startLua() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);

		m_setupFunctions();

		//lua.script_file("mods/examplemod/config/script.lua");

		// Here, we are binding the member function and a class instance: it will call the function on
		// the given class instance
		//lua.set_function("spawnObj", &LuaManager::spawnRandomObj, LuaManager());

		// With no bound instance:
		//lua.set("obj", my_class(24));
	}

	// todo
	void loadMods() {

		// go through mods folder, open it's mod.xml file and follow it's instructions
	}

private:

	// informs lua about functions.
	void m_setupFunctions() {
		lua.set_function("enableCur", [] {EnableCursor(); });
		lua.set_function("disableCur", [] {DisableCursor(); });
		lua.set_function("tsVer", [] {TechStorm::Logman::customLog(LOG_INFO, TextFormat("TechStorm's Installed Version is %s.", TECHSTORM_VERSION)); });
		lua.set_function("tsrVer", [] {TechStorm::Logman::customLog(LOG_INFO, TextFormat("TechStorm-Rivalry's Installed Version is %s.", VERSION)); });
		lua.set_function("exit", [] {exit(0); });

		lua.set_function("enableWM", [] {rlEnableWireMode(); });
		lua.set_function("disableWM", [] {rlDisableWireMode(); });
		lua.set_function("reloadShader", [] {});
	}
};
