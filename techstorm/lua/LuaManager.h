#pragma once
#include "../Common.h"
//#include "raylib-lua-sol.hpp"
#include <tuple>
#include <cassert>
#include <utility> // for std::pair

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

	void log(std::string b) {
		Logman::Log(b.c_str());
	}

	void startLua() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);

		//raylib_lua_sol(this->lua);

		lua.script_file("mods/examplemod/config/script.lua");
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
};
