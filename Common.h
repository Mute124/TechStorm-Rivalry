/*
    This file will contain all the common headers used in the project. That way it can be updated easily.
*/
#pragma once
#include "../build/_deps/raylib-src/src/raylib.h"
#include "../build/_deps/raylib-src/src/raymath.h"
#include "../build/_deps/raylib-src/src/rlgl.h"
#include "../build/_deps/raylib-src/src/rcamera.h"
#include "../build/_deps/raygui-src/src/raygui.h"
// End of raylib Libraries


// C++ Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdarg>
#include <thread>
// End of C++ Libraries

// Internal Libraries

#include "Engine/Classes/ConfigMan/ConfigMan.h"

#include "Engine/Classes/Logging/Logman.h"

// End of Internal Libraries

// External Libraries

// Jolt Physics Library

#include "../build/_deps/joltphysics-src/Jolt/Jolt.h"

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

// End of External Libraries


// End of Common.h