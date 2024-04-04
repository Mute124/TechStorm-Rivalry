/*
* This file shall hold ONLY HEADERS, any functions/variables/etc will go into Globals.h and Globals.cpp.
*
* Any headers added here are considered commonly used, or simply provide utilities to the engine. Please sort them into the correct section.
*/
#pragma once
#define SOL_ALL_SAFETIES_ON 1
#define _CRT_SECURE_NO_WARNINGS

// framework(s) / external libraries
#include <raylib.h>
#include <raymath.h>
#include "lib/rcamera.h"
#define RAYGUI_IMPLEMENTATION
#include "lib/raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again

// C++ Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <math.h>
#include <cassert>

// lua
#include <lua.hpp>
#include <sol/sol.hpp>

// config
#include <toml++/toml.hpp>
#include <tinyxml2.h>

// Project Chrono declaration

// Engine Includes
#include "Globals.h"
#include "core/TechStorm.h"
#include "core/config/Configman.h"
#include "core/logging/Logman.h"
#include "core/obj/Gameobject.h"
#include "core/utils/Math.h"
#include "core/registry/Registry.h"
#include "core/utils/ArrayUtils.h"
#include "core/audio/FxMan.h"
#include "core/ui/UIMan.h"

#include "TechStorm-Rivalry.h"
#include "Game.h"
#include "env/GameDirector.h"

// end of common.h
