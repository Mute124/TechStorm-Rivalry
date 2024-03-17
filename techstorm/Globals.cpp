#include "Globals.h"
#include "rlgl.h"
#include <stdlib.h>
#include <any>
#include <stdio.h>
#include <vector>

// Not needed but makes things look nicer
Model GetDefaultModel() {
	return defaultModel;
}

// Not needed but makes things look nicer
void SetDefaultModel(Model model) {
	defaultModel = model;
}

Texture GetDefaultTexture() {
	return LoadTexture("resources/textures/default.png");
}

/**
 * Returns a CubeVerticies object with all coordinates initialized to 0.0f.
 */
CubeVerticies CubeVertZero() {
	return CubeVerticies{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
}

// Returns the vertices of a cube with all coordinates set to 1.0f
CubeVerticies CubeVertOne() {
	return CubeVerticies{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
}

/*
* Generate a custom mesh based on the provided vertices.
*
* @param verts - The vertices defining the mesh
* @return The generated mesh
*/
Mesh GenMeshCustomT(TriVert verts)
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
}

bool CheckCollisionRayBox(Ray ray, BoundingBox box, float* outDistance)
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

Vector3 CameraToWorld(Camera3D camera)
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

float Mean(const std::vector<float>& data)
{
	float result = 0.0;
	for (unsigned int i = 1; i < data.size(); i++)
	{
		result += data[i - 1] + data[i];
	}
	return result / data.size();
}

Vector3 Vector3RandomControlled(Vector3 start, int minDeviation, int maxDeviation)
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

float Invert(float Value)
{
	return -Value;
}

Vector3 Vector3Random(int min, int max)
{
	return Vector3{ static_cast<float>(GetRandomValue(min, max)),
					 static_cast<float>(GetRandomValue(min, max)),
					 static_cast<float>(GetRandomValue(min, max)) };
}

Vector3 RoundVec3(Vector3 Target)
{
	return Vector3{
		(float)round(Target.x), (float)round(Target.y), (float)round(Target.z) };
}

Vector3 Vector3MaxPos()
{
	return Vector3{ WORLD_SIZE, WORLD_SIZE, WORLD_SIZE };
}

Vector3 Vector3RandomEx(Vector3 min, Vector3 max)
{
	return Vector3{ (float)GetRandomValue(min.x, max.x), (float)GetRandomValue(min.y, max.y), (float)GetRandomValue(min.z, max.z) };
}

Vector3 Vector3Pow(Vector3 vec, float exp) {
	return Vector3{ powf(vec.x, exp), powf(vec.y, exp), powf(vec.z, exp) };
}

float Vector3Dist(Vector3 v1, Vector3 v2) {
	return sqrt(
		powf((v2.x - v1.x), 2.0f) +
		powf((v2.y - v1.y), 2.0f) +
		powf((v2.z - v1.z), 2.0f));
}

float Vector3Avg(Vector3 vec) {
	double sum = vec.x + vec.y + vec.z;

	return sum / 3;
}
static Mesh GenMeshCustom(void)
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

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126)) keyPressed = true;

	return keyPressed;
}
