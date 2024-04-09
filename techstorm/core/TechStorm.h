// this file contains commons for TechStorm
#pragma once
#define SOL_ALL_SAFETIES_ON 1

#include "TechStormOptions.h" // this is where the engine config is.
#include "TechStormCommon.h" // do not include this file in your project, only include TechStorm.h
#include "TechStormGlobals.h"
#include <raylib.h>
#include <raymath.h>
#include "../lib/rcamera.h"

// C++ Libraries
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
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
#include "universalTypes/uVec2.h"
#include "universalTypes/uVec3.h"
#include "universalTypes/uVec4.h"
#include "universalTypes/uColor.h"

namespace TechStorm {
	using namespace TechStorm;
}
