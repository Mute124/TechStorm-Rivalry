// -----------------------------------------------------------------------------
// Ownership information
// -----------------------------------------------------------------------------
#ifndef AUTHOR
#define AUTHOR MutedTea
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif
// TODO : clean up this mess of a file. Now that we have a config system, we need to clean this up
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "core/utils/Math.h"
#include "rlgl.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "core/logging/Logman.h"

// Plain structures in C++ (without constructors) can be initialized with { }
#if defined(__cplusplus)
#define CLITERAL(type) type
#else
#define CLITERAL(type) (type)
#endif
// -----------------------------------------------------------------------------
// Engine Constants
// -----------------------------------------------------------------------------

// When objects should disapear from view
#ifndef DEFAULT_NEAR_CULL_DISTANCE
#define DEFAULT_NEAR_CULL_DISTANCE 0.01 // Default near cull distance
#endif
#ifndef DEFAULT_FAR_CULL_DISTANCE
#define DEFAULT_FAR_CULL_DISTANCE 50000.0 // Default far cull distance
#endif

#define NUM_FRAMES 3          // Number of frames (rectangles) for the button sprite texture

// Max amount of objects. Unused for now, will eventually be used later on.
#define MAX_INSTANCES 10000

// Max amount of loaded shaders. Unused for right now
#define MAX_SHADERS 10

// -----------------------------------------------------------------------------
// Skybox Constants
// -----------------------------------------------------------------------------

// How big the skybox is. (This doesnt have to be a huge number)
#define SKYBOX_SIZE 1.0f

// -----------------------------------------------------------------------------
// World Constants
// -----------------------------------------------------------------------------
#define WORLD_SIZE 100 // This is a global that defines how large the world will be.
#define BLOCK_SIZE 1   // Default Block size. Changing this variable will affect the size of all blocks.

// How far away something should cease from the plane of existance until it is forced back to the plane of existance.
#define DESPAWN_DISTANCE 1000.0f

// -----------------------------------------------------------------------------
// Type Shortenings
// -----------------------------------------------------------------------------

// alternative cases. makes it so that you dont have to write as much boiler plate code. (Also simply faster)
// Works by providing an Alias.

// Texture filtering and clamping
#define FILTER_BILINEAR TEXTURE_FILTER_BILINEAR
#define WRAP_CLAMP TEXTURE_WRAP_CLAMP

// Shader crap
#define UNIFORM_VEC4 SHADER_UNIFORM_VEC4
#define UNIFORM_VEC3 SHADER_UNIFORM_VEC3
#define UNIFORM_INT SHADER_UNIFORM_INT
#define UNIFORM_FLOAT SHADER_UNIFORM_FLOAT
#define MAP_CUBEMAP SHADER_LOC_MAP_CUBEMAP
#define MAP_IRRADIANCE SHADER_LOC_MAP_IRRADIANCE
#define LOC_VECTOR_VIEW LOC_VECTOR_VIEW // TODO : Check if this is nessisary.
#define LOG_WARN LOG_WARNING // just to make typing easier.

// Determines what GLSL version will be used.
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#define MAX_KEYBINDS 40

// -----------------------------------------------------------------------------
// Utilities
// -----------------------------------------------------------------------------

// Types

// the same as Vector2 but with int
typedef struct
{
	int x;
	int y;
} intVec2;

// the same as Vector3 but with ints
typedef struct
{
	int x;
	int y;
	int z;
} intVec3;

// for use where you need to have a equal reflection. So it will be both positive vector3 and negative
typedef struct
{
	Vector3 p;
	Vector3 n;
} DualVec3;

// The verticies of a cube
typedef struct
{
	/*
		Verticies Diagram
			V7 - - - - - -v6
		   /             / |
		V1 - - - - V2 /    |
  `     |    |      |      |
		|    v8 - - |- - - |
		|   /       |      V5
		| /         |    /
		V3 - - - -  V4 /

	*/

	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 v4;
	Vector3 v5;
	Vector3 v6;
	Vector3 v7;
	Vector3 v8;
} CubeVerticies;

// This is an artificial triangle. Not used at the moment.
// Triangle Verticies
typedef struct
{
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
} TriVert;

// Physics crap
/*
* All units are in the METRIC system.
*/
#define CelestialPlane double
#define GravitationalConstant double
#define GravitationalConstantParameter double
#define Eccentricity int
#define Energy double
#define Force double

// A position on a celestial plane
typedef struct CelestialVector {
	double x;
	double z;
};

typedef struct CelestialOrbit : public CelestialVector {
	double r; // distance from well
	int eccentricity; // min=0 max=1
	double frequency;
};

typedef struct Collision {
	Force force;
};

// a global model that can be used if no model is present, or it can be used for testing. Set in main.cpp
static Model defaultModel = { 0 };

//static std::map<const char*, KeyboardKey> GlobalKeyBinds;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

extern Model GetDefaultModel();
extern void SetDefaultModel(Model model);
extern Texture GetDefaultTexture();
// Mesh Tools
extern CubeVerticies CubeVertZero();	// Returns a null cube verticies type
extern CubeVerticies CubeVertOne();

// Todo : make this more modular
extern Mesh GenMeshCustom(TriVert verts); // Generates a mesh from a triangle verticies
extern TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format);
// Collisions
extern bool CheckCollisionRayBox(Ray ray, BoundingBox box, float* outDistance);

// Math
extern Vector3 CameraToWorld(Camera3D camera);
extern float Mean(const std::vector<float>& data);
extern Vector3 Vector3RandomControlled(Vector3 start, int minDeviation, int maxDeviation);
extern float Invert(float Value);
extern Vector3 Vector3Random(int min, int max);
extern Vector3 RoundVec3(Vector3 Target);
extern Vector3 Vector3MaxPos();
extern Vector3 Vector3RandomEx(Vector3 min, Vector3 max);

extern float Vector3Avg(Vector3 vec);
extern Vector3 Vector3DstAvg(Vector3 v1, Vector3 v2);

static void PrintFloat(const char* name, float val) {
	Logman::Log(TextFormat("Value of %s is %f", name, val));
}
