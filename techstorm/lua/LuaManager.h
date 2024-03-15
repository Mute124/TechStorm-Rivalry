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

	void init() {
		startLua();
		loadMods();
	}

	void startLua() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);

		//raylib_lua_sol(this->lua);

		lua.script_file("mods/examplemod/config/script.lua");
		// the type "sol::state" behaves
		// exactly like a table!
		bool isfullscreen = lua["config"]["fullscreen"]; // can get nested variables
		sol::table config = lua["config"];
		Logman::Log(TextFormat("result : %i", config[1]));
		//c_assert(!isfullscreen);
	}

	// todo
	void loadMods() {
		// go through mods folder, open it's mod.xml file and follow it's instructions
	}
};
