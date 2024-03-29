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

// frameworks

#include "raylib.h"
#include <raymath.h>

#include "core/utils/Math.h"
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

// Not needed but makes things look nicer
inline Model GetDefaultModel() {
	return defaultModel;
}

// Not needed but makes things look nicer
inline void SetDefaultModel(Model model) {
	defaultModel = model;
}
inline Texture GetDefaultTexture() {
	return LoadTexture("resources/textures/default.png");
}
float Vector3Dist(Vector3 v1, Vector3 v2) {
	return sqrt(
		powf((v2.x - v1.x), 2.0f) +
		powf((v2.y - v1.y), 2.0f) +
		powf((v2.z - v1.z), 2.0f));
}

// Mesh Tools
/**
* Returns a CubeVerticies object with all coordinates initialized to 0.0f.
*/
inline CubeVerticies CubeVertZero() {
	return CubeVerticies{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
}	// Returns a null cube verticies type

	// Returns the vertices of a cube with all coordinates set to 1.0f
inline CubeVerticies CubeVertOne() {
	return CubeVerticies{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
}

// Todo : make this more modular
inline Mesh GenMeshCustom(void)
{
	Mesh mesh = { 0 };
	mesh.triangleCount = 2;
	mesh.vertexCount = mesh.triangleCount * 4;
	mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
	mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
	mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

	// Vertex at (0, 0, 0)
	mesh.vertices[0] = 0;
	mesh.vertices[1] = 0;
	mesh.vertices[2] = 0;
	mesh.normals[0] = 0;
	mesh.normals[1] = 1;
	mesh.normals[2] = 0;
	mesh.texcoords[0] = 0;
	mesh.texcoords[1] = 0;

	// Vertex at (1, 0, 2)
	mesh.vertices[3] = 1;
	mesh.vertices[4] = 0;
	mesh.vertices[5] = 2;
	mesh.normals[3] = 0;
	mesh.normals[4] = 1;
	mesh.normals[5] = 0;
	mesh.texcoords[2] = 0.5f;
	mesh.texcoords[3] = 1.0f;

	// Vertex at (2, 0, 0)
	mesh.vertices[6] = 2;
	mesh.vertices[7] = 0;
	mesh.vertices[8] = 0;
	mesh.normals[6] = 0;
	mesh.normals[7] = 1;
	mesh.normals[8] = 0;
	mesh.texcoords[4] = 1;
	mesh.texcoords[5] = 0;

	// Vertex at (2, 0, 0)
	mesh.vertices[9] = 3;
	mesh.vertices[10] = 0;
	mesh.vertices[11] = 0;
	mesh.normals[9] = 0;
	mesh.normals[10] = 2;
	mesh.normals[11] = 0;
	mesh.texcoords[6] = 1;
	mesh.texcoords[7] = 1;

	// Upload mesh data from CPU (RAM) to GPU (VRAM) memory
	UploadMesh(&mesh, true);

	return mesh;
}
/*
* Generate a custom mesh based on the provided vertices.
*
* @param verts - The vertices defining the mesh
* @return The generated mesh
*/
inline Mesh GenMeshCustomT(TriVert verts)
{
	// Initialize a new mesh
	Mesh mesh = { 0 };
	mesh.triangleCount = 1;
	mesh.vertexCount = mesh.triangleCount * 3;

	// Allocate memory for vertices, texture coordinates, and normals
	mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));  // 3 vertices, 3 coordinates each (x, y, z)
	mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));  // 3 vertices, 2 coordinates each (x, y)
	mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));   // 3 vertices, 3 coordinates each (x, y, z)

	// Set vertex data
	mesh.vertices[0] = verts.v1.x;
	mesh.vertices[1] = verts.v2.x;
	mesh.vertices[2] = verts.v3.x;
	mesh.normals[0] = verts.v1.x;
	mesh.normals[1] = verts.v2.x;
	mesh.normals[2] = verts.v3.x;
	mesh.texcoords[0] = 0;
	mesh.texcoords[1] = 0;

	mesh.vertices[3] = verts.v1.y;
	mesh.vertices[4] = verts.v2.y;
	mesh.vertices[5] = verts.v3.y;
	mesh.normals[3] = verts.v1.y;
	mesh.normals[4] = verts.v2.y;
	mesh.normals[5] = verts.v3.y;
	mesh.texcoords[2] = 0.5f;
	mesh.texcoords[3] = 1.0f;

	mesh.vertices[6] = verts.v1.z;
	mesh.vertices[7] = verts.v2.z;
	mesh.vertices[8] = verts.v3.z;
	mesh.normals[6] = verts.v3.z;
	mesh.normals[7] = verts.v3.z;
	mesh.normals[8] = verts.v3.z;
	mesh.texcoords[4] = 1;
	mesh.texcoords[5] = 0;

	// Upload mesh data from CPU (RAM) to GPU (VRAM) memory
	UploadMesh(&mesh, false);

	return mesh;
} // Generates a mesh from a triangle verticies

// Collisions
inline bool CheckCollisionRayBox(Ray ray, BoundingBox box, float* outDistance)
{
	// Compute the inverse of the ray direction
	Vector3 invDir = { 1.0f / ray.direction.x, 1.0f / ray.direction.y,
		1.0f / ray.direction.z };

	// Compute the sign of the inverse direction
	int signX = (invDir.x < 0.0f) ? 1 : 0;
	int signY = (invDir.y < 0.0f) ? 1 : 0;
	int signZ = (invDir.z < 0.0f) ? 1 : 0;

	// Compute the min and max values for each axis
	float tmin = (box.min.x - ray.position.x) * invDir.x;
	float tmax = (box.max.x - ray.position.x) * invDir.x;
	float tymin = (box.min.y - ray.position.y) * invDir.y;
	float tymax = (box.max.y - ray.position.y) * invDir.y;

	// Swap the min and max values if necessary
	if (tmin > tmax)
	{
		float temp = tmin;
		tmin = tmax;
		tmax = temp;
	}

	if (tymin > tymax)
	{
		float temp = tymin;
		tymin = tymax;
		tymax = temp;
	}

	// Check for a miss
	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	// Compute the final min and max values for each axis
	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	float tzmin = (box.min.z - ray.position.z) * invDir.z;
	float tzmax = (box.max.z - ray.position.z) * invDir.z;

	// Swap the min and max values if necessary
	if (tzmin > tzmax)
	{
		float temp = tzmin;
		tzmin = tzmax;
		tzmax = temp;
	}

	// Check for a miss
	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	// Compute the final min and max values for each axis
	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	// Store the distance to the box in the output variable
	if (outDistance)
	{
		*outDistance = tmin;
	}

	// The ray intersects the box
	return true;
}

// Math
inline Vector3 CameraToWorld(Camera3D camera)
{
	float distance;

	// Calculate the ray from the camera to the mouse position
	Vector2 mousePos = GetMousePosition();
	Vector3 mousePos3 = { mousePos.x, mousePos.y, 0 };

	// Get the direction vector of the ray
	Vector3 rayDirection =
		Vector3Normalize(Vector3Subtract(mousePos3, camera.position));

	// Multiply the direction vector with a scalar value to increase the length of
	// the ray
	float rayLength = 40.0f;
	rayDirection = Vector3Scale(rayDirection, rayLength);

	// Create the ray with the modified direction
	Ray ray = { camera.position, rayDirection };

	// Calculate the distance from the camera to the ground plane
	distance = -(camera.position.y / ray.position.y);

	// Calculate the point where the ray intersects the ground plane
	Vector3 groundPoint =
		Vector3Add(camera.position, Vector3Scale(ray.position, distance));

	return groundPoint;
}
inline float Mean(const std::vector<float>& data)
{
	float result = 0.0;
	for (unsigned int i = 1; i < data.size(); i++)
	{
		result += data[i - 1] + data[i];
	}
	return result / data.size();
}
inline Vector3 Vector3RandomControlled(Vector3 start, int minDeviation, int maxDeviation)
{
	Vector3 result = start;

	int roll = GetRandomValue(1, 3);
	int deviationRoll = GetRandomValue(0, 1);

	if (roll == 1)
	{
		result.x += (float)GetRandomValue(minDeviation, maxDeviation) + minDeviation;
		result.y += minDeviation;
		result.z += minDeviation;

		if (deviationRoll == 1)
		{
			result.x += minDeviation;
		}
		else
		{
			result.x -= minDeviation;
		}
	}
	else if (roll == 2)
	{
		result.y += (float)GetRandomValue(minDeviation, maxDeviation);
		result.z += minDeviation;

		if (deviationRoll == 1)
		{
			result.y += minDeviation;
		}
		else
		{
			result.y -= minDeviation;
		}
	}
	else
	{
		result.x += minDeviation;
		result.y += minDeviation;
		result.z += minDeviation;

		if (deviationRoll == 1)
		{
			result.z += (float)GetRandomValue(minDeviation, maxDeviation);
		}
		else
		{
			result.z -= (float)GetRandomValue(minDeviation, maxDeviation);
		}
	}

	return result;
}
inline float Invert(float Value)
{
	return -Value;
}
inline Vector3 Vector3Random(int min, int max)
{
	return Vector3{ static_cast<float>(GetRandomValue(min, max)),
		static_cast<float>(GetRandomValue(min, max)),
		static_cast<float>(GetRandomValue(min, max)) };
}
inline Vector3 RoundVec3(Vector3 Target)
{
	return Vector3{
		(float)round(Target.x), (float)round(Target.y), (float)round(Target.z) };
}
inline Vector3 Vector3MaxPos()
{
	return Vector3{ WORLD_SIZE, WORLD_SIZE, WORLD_SIZE };
}
inline Vector3 Vector3RandomEx(Vector3 min, Vector3 max)
{
	return Vector3{ (float)GetRandomValue(min.x, max.x), (float)GetRandomValue(min.y, max.y), (float)GetRandomValue(min.z, max.z) };
}

inline float Vector3Avg(Vector3 vec) {
	double sum = vec.x + vec.y + vec.z;

	return sum / 3;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
inline bool IsAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126)) keyPressed = true;

	return keyPressed;
}

/*
* //--------------------------------------------------------------------------------------------

// Load/Save/Export data functions
//--------------------------------------------------------------------------------------------
// Load layout from text file
// NOTE: If NULL provided, an empty layout is initialized
static GuiLayout* LoadLayout(const char* fileName)
{
	GuiLayout* layout = (GuiLayout*)RL_CALLOC(1, sizeof(GuiLayout));

	ResetLayout(layout);    // Init some default values

	if (fileName != NULL)   // Try loading text layout file
	{
		FILE* rglFile = fopen(fileName, "rt");

		if (rglFile != NULL)
		{
			char buffer[256] = { 0 };
			char anchorName[MAX_ANCHOR_NAME_LENGTH] = { 0 };

			fgets(buffer, 256, rglFile);

			while (!feof(rglFile))
			{
				switch (buffer[0])
				{
				case 'r':
				{
					sscanf(buffer, "r %f %f %f %f", &layout->refWindow.x, &layout->refWindow.y, &layout->refWindow.width, &layout->refWindow.height);

					// NOTE: Reference window defines anchor[0]
					layout->anchors[0].id = 0;
					layout->anchors[0].ap = NULL;
					layout->anchors[0].x = layout->refWindow.x;
					layout->anchors[0].y = layout->refWindow.y;
					layout->anchors[0].enabled = true;
					strcpy(layout->anchors[0].name, "refPoint");

					layout->anchorCount++;
				} break;
				case 'a':
				{
					int enabled = 0;
					sscanf(buffer, "a %d %s %d %d %d",
						&layout->anchors[layout->anchorCount].id,
						anchorName,
						&layout->anchors[layout->anchorCount].x,
						&layout->anchors[layout->anchorCount].y,
						&enabled);

					if (layout->anchors[layout->anchorCount].id > 0)
					{
						layout->anchors[layout->anchorCount].enabled = (enabled ? true : false);
						strcpy(layout->anchors[layout->anchorCount].name, anchorName);

						layout->anchorCount++;
					}
				} break;
				case 'c':
				{
					int anchorId = 0;
					sscanf(buffer, "c %d %d %s %f %f %f %f %d %[^\n]s",
						&layout->controls[layout->controlCount].id,
						&layout->controls[layout->controlCount].type,
						layout->controls[layout->controlCount].name,
						&layout->controls[layout->controlCount].rec.x,
						&layout->controls[layout->controlCount].rec.y,
						&layout->controls[layout->controlCount].rec.width,
						&layout->controls[layout->controlCount].rec.height,
						&anchorId,
						layout->controls[layout->controlCount].text);

					layout->controls[layout->controlCount].ap = &layout->anchors[anchorId];

					// NOTE: refWindow offset (anchor[0]) must be added to controls with no anchor
					if (anchorId == 0)
					{
						layout->controls[layout->controlCount].rec.x += layout->refWindow.x;
						layout->controls[layout->controlCount].rec.y += layout->refWindow.y;
					}

					layout->controlCount++;
				} break;
				default: break;
				}

				fgets(buffer, 256, rglFile);
			}

			fclose(rglFile);

			// NOTE: refWindow offset (anchor[0]) must be added to all anchors
			for (int i = 1; i < layout->anchorCount; i++)
			{
				layout->anchors[i].x += layout->refWindow.x;
				layout->anchors[i].y += layout->refWindow.y;
			}
		}
	}
	else
	{
		// Define reference anchor
		layout->anchors[0].x = 0;
		layout->anchors[0].y = 40;
		layout->anchors[0].enabled = true;
		layout->refWindow.x = 0;
		layout->refWindow.y = 40;
		layout->anchorCount = 1;
	}

	return layout;
}

// Unload layout
static void UnloadLayout(GuiLayout* layout)
{
	RL_FREE(layout);
}

// Reset layout to default values
static void ResetLayout(GuiLayout* layout)
{
	// Set anchor points to default values
	for (int i = 0; i < MAX_ANCHOR_POINTS; i++)
	{
		layout->anchors[i].id = i;
		layout->anchors[i].x = 0;
		layout->anchors[i].y = 0;
		layout->anchors[i].enabled = false;
		layout->anchors[i].hidding = false;
		memset(layout->anchors[i].name, 0, MAX_ANCHOR_NAME_LENGTH);

		if (i == 0) strcpy(layout->anchors[i].name, "refPoint");
		else strcpy(layout->anchors[i].name, TextFormat("anchor%02i", i));
	}

	// Initialize layout controls data
	for (int i = 0; i < MAX_GUI_CONTROLS; i++)
	{
		layout->controls[i].id = 0;
		layout->controls[i].type = 0;
		layout->controls[i].rec = (Rectangle){ 0, 0, 0, 0 };
		memset(layout->controls[i].text, 0, MAX_CONTROL_TEXT_LENGTH);
		memset(layout->controls[i].name, 0, MAX_CONTROL_NAME_LENGTH);
		layout->controls[i].ap = &layout->anchors[0];  // By default, set parent anchor
	}

	layout->refWindow = (Rectangle){ 0, 40, -1, -1 };
	layout->anchorCount = 0;
	layout->controlCount = 0;
}

// Save layout information as text file
static void SaveLayout(GuiLayout* layout, const char* fileName)
{
#define RGL_FILE_VERSION_TEXT "4.0"

	FILE* rglFile = fopen(fileName, "wt");

	if (rglFile != NULL)
	{
		// Write some description comments
		fprintf(rglFile, "#\n# rgl layout text file (v%s) - raygui layout file generated using rGuiLayout\n#\n", RGL_FILE_VERSION_TEXT);
		fprintf(rglFile, "# Number of controls:     %i\n#\n", layout->controlCount);
		fprintf(rglFile, "# Ref. window:    r <x> <y> <width> <height>\n");
		fprintf(rglFile, "# Anchor info:    a <id> <name> <posx> <posy> <enabled>\n");
		fprintf(rglFile, "# Control info:   c <id> <type> <name> <rectangle> <anchor_id> <text>\n#\n");

		// Write reference window and reference anchor (anchor[0])
		fprintf(rglFile, "r %i %i %i %i\n", (int)layout->refWindow.x, (int)layout->refWindow.y, (int)layout->refWindow.width, (int)layout->refWindow.height);

		//fprintf(rglFile, "a %03i %s %i %i %i\n", layout->anchors[0].id, layout->anchors[0].name, layout->anchors[0].x, layout->anchors[0].y, layout->anchors[0].enabled);

		for (int i = 1; i < MAX_ANCHOR_POINTS; i++)
		{
			if (layout->anchors[i].enabled)
			{
				fprintf(rglFile, "a %03i %s %i %i %i\n",
					layout->anchors[i].id,
					layout->anchors[i].name,
					(int)(layout->anchors[i].x - (int)layout->refWindow.x),
					(int)(layout->anchors[i].y - (int)layout->refWindow.y),
					layout->anchors[i].enabled);
			}
		}

		for (int i = 0; i < layout->controlCount; i++)
		{
			if (layout->controls[i].ap->id == 0)
			{
				fprintf(rglFile, "c %03i %i %s %i %i %i %i %i %s\n",
					layout->controls[i].id,
					layout->controls[i].type,
					layout->controls[i].name,
					(int)layout->controls[i].rec.x - (int)layout->refWindow.x,
					(int)layout->controls[i].rec.y - (int)layout->refWindow.y,
					(int)layout->controls[i].rec.width,
					(int)layout->controls[i].rec.height,
					layout->controls[i].ap->id,
					layout->controls[i].text);
			}
			else
			{
				fprintf(rglFile, "c %03i %i %s %i %i %i %i %i %s\n",
					layout->controls[i].id,
					layout->controls[i].type,
					layout->controls[i].name,
					(int)layout->controls[i].rec.x,
					(int)layout->controls[i].rec.y,
					(int)layout->controls[i].rec.width,
					(int)layout->controls[i].rec.height,
					layout->controls[i].ap->id,
					layout->controls[i].text);
			}
		}

		fclose(rglFile);
	}

	/*
		if (binary)
		{
			#define RGL_FILE_VERSION_BINARY 400

			FILE *rglFile = fopen(fileName, "wb");

			if (rglFile != NULL)
			{
				// Layout File Structure (.rgl)
				// ------------------------------------------------------
				// Offset  | Size    | Type       | Description
				// ------------------------------------------------------
				// 0       | 4       | char       | Signature: "rGL "
				// 4       | 2       | short      | Version: 200
				// 6       | 2       | short      | reserved
				//
				// Ref window data
				// 8       | 4       | int        | ref window x
				// 12      | 4       | int        | ref window x
				// 16      | 4       | int        | ref window width
				// 20      | 4       | int        | ref window height
				//
				// Anchor info data:    a <id> <name> <posx> <posy> <enabled>\n");
				// 24      | 4       | int        | Anchor count
				// for (i = 1; i < anchorCount; i++)
				// {
				//    x    | 4       | int        | Anchor id
				//    x    | 64      | char       | Anchor name
				//    x    | 4       | int        | Anchor posX
				//    x    | 4       | int        | Anchor posY
				//    x    | 4       | int        | Anchor enabled?
				// }
				//
				// Control info data:   c <id> <type> <name> <rectangle> <anchor_id> <text>\n#\n")
				// x       | 4       | int        | Control count
				// for (i = 0; i < countCount; i++)
				// {
				//    x    | 4       | int        | Control id
				//    x    | 4       | int        | Control type
				//    x    | 64      | char       | Control name
				//    x    | 4       | int        | Control rec x
				//    x    | 4       | int        | Control rec y
				//    x    | 4       | int        | Control rec width
				//    x    | 4       | int        | Control rec height
				//    x    | 4       | int        | Control anchor id
				//    x    | 128     | char       | Control text
				// }

				char signature[5] = "rGL ";
				short version = RGL_FILE_VERSION_BINARY;
				short reserved = 0;

				fwrite(signature, 1, 4, rglFile);
				fwrite(&version, sizeof(short), 1, rglFile);
				fwrite(&reserved, sizeof(short), 1, rglFile);

				int rec[4] = { (int)layout->refWindow.x, (int)layout->refWindow.y, (int)layout->refWindow.width, (int)layout->refWindow.height };
				fwrite(&rec[0], sizeof(int), 1, rglFile);
				fwrite(&rec[1], sizeof(int), 1, rglFile);
				fwrite(&rec[2], sizeof(int), 1, rglFile);
				fwrite(&rec[3], sizeof(int), 1, rglFile);

				fwrite(&layout->anchorCount, sizeof(int), 1, rglFile);

				// WARNING: anchor[0] is already implicit in ref window
				for (int i = 1, x = 0, y = 0, e = 0; i < anchorCount; i++)
				{
					fwrite(&layout->anchors[i].id, sizeof(int), 1, rglFile); // Anchor id
					fwrite(&layout->anchors[i].name, sizeof(char), MAX_ANCHOR_NAME_LENGTH, rglFile); // Anchor name
					x = (int)(layout->anchors[i].x - (int)layout->refWindow.x);
					fwrite(&x, sizeof(int), 1, rglFile); // Anchor posX
					y = (int)(layout->anchors[i].y - (int)layout->refWindow.y),
					fwrite(&y, sizeof(int), 1, rglFile); // Anchor posY
					e = (layout->anchors[i].enabled? 1 : 0);
					fwrite(&e, sizeof(int), 1, rglFile); // Anchor enabled?
				}

				fwrite(&layout->controlCount, sizeof(int), 1, rglFile);

				for (int i = 0; i < countCount; i++)
				{
					fwrite(&layout->controls[i].id, sizeof(int), 1, rglFile); // Control id
					fwrite(&layout->controls[i].type, sizeof(int), 1, rglFile); // Control type
					fwrite(&layout->controls[i].name, sizeof(char), MAX_CONTROL_NAME_LENGTH, rglFile); // Control name
					rec = (Rectangle){ (int)layout->controls[i].rec.x, (int)layout->controls[i].rec.y, (int)layout->controls[i].rec.width, (int)layout->controls[i].rec.height };
					fwrite(&rec[0], sizeof(int), 1, rglFile); // Control rec x
					fwrite(&rec[1], sizeof(int), 1, rglFile); // Control rec y
					fwrite(&rec[2], sizeof(int), 1, rglFile); // Control rec width
					fwrite(&rec[3], sizeof(int), 1, rglFile); // Control rec height
					fwrite(&layout->controls[i].ap->id, sizeof(int), 1, rglFile); // Control anchor id
					fwrite(&layout->controls[i].text, sizeof(char), MAX_CONTROL_TEXT_LENGTH, rglFile); // Control text
				}

				fclose(rglFile);
			}
		}
}

*/
