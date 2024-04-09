// this file contains commons for TechStorm
#pragma once
#include "TechStormOptions.h" // this is where the engine config is.
#include "TechStormGlobals.h"

#ifdef TECHSTORM_EXPORTS
#define TECHSTORM_API __declspec(dllexport)
#else
#define TECHSTORM_API __declspec(dllimport)
#endif
