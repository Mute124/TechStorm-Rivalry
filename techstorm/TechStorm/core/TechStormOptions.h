#pragma once

// Comment the below line if you want to customize your experience
#define TECHSTORM_DEFAULT_SETTINGS
#define TECHSTORM_DEFAULT_QOL
// by defining this you signify you would like quality of life modules/features
// Not needed but they make it easier for you.
#ifdef TECHSTORM_DEFAULT_QOL
#define USE_QOL true
#else
#define USE_QOL false
#endif // TECHSTORM_DEFAULT_QOL

#ifdef TECHSTORM_DEFAULT_SETTINGS
#define TECHSTORM_ENABLE_CONFIG  // define to enable the usage of TechStorm's config management system
#define TECHSTORM_ENGINE_3D
#define TECHSTORM_DEFAULT_IMPLEMENTATION

// If there is no defines regarding making the engine 3d, then we can interpolate we are in 2d mode.
#ifndef TECHSTORM_ENGINE_3D
// if QOL is enabled, we will automatically set it to 2d as 3d was not defined.
#if USE_QOL == true
#define TECHSTORM_ENGINE_2D
#endif // !TECHSTORM_ENGINE_3D

#endif
#else

// by defining this you signify you do NOT want the default settings. Please define your settings
#ifdef TECHSTORM_CUSTOM_SETTINGS

#else
#error You must define a valid settings parameter within the TechStormOptions header!
#endif // TECHSTORM_CUSTOM_SETTINGS

// Add your custom config in here if you enabled custom settings.

#endif // TECHSTORM_DEFAULT_SETTINGS

// Check if No draw mode was selected.
#ifndef TECHSTORM_ENGINE_3D || TECHSTORM_ENGINE_2D
#error You must define what render mode you want within the TechStormOptions header!
#endif // !TECHSTORM_ENGINE_3D || TECHSTORM_ENGINE_2D
#pragma
