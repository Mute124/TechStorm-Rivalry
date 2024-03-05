/*
* This file shall hold ONLY HEADERS, any functions/variables/etc will go into Globals.h and Globals.cpp.
*
* Any headers added here are considered commonly used, or simply provide utilities to the engine. Please sort them into the correct section.
*/
#pragma once
// framework(s)
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "lib/raygui.h"
#include "lib/rcamera.h"
#include "lib/yse/yse.hpp"
#include "lib/toml.h"

// C++ Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <math.h>

// Engine Includes
#include "core/config/Configman.h"
#include "core/logging/Logman.h"
#include "core/obj/Gameobject.h"
#include "core/utils/Math.h"
#include "core/registry/Registry.h"
#include "core/scripting/ScriptManager.h"
#include "core/scripting/IScriptable.h"
#include "core/utils/ArrayUtils.h"
#include "Globals.h"
#include "core/audio/FxMan.h"
#include "core/ui/UIMan.h"
// end of common.h
