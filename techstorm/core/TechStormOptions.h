#pragma once
#define ENABLE_CONFIG  // define to enable the usage of TechStorm's config management system
#define ENGINE_3D

// If there is no defines regarding making the engine 3d, then we can interpolate we are in 2d mode.
#ifndef ENGINE_3D
#define ENGINE_2D
#endif // !ENGINE_3D
