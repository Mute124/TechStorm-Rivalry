// TODO : clean up this mess of a file. Now that we have a config system, we need to clean this up

#pragma once
#include "../../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>   // For debugging purposes
#include <thread>     // needed for threading
#include <vector>     // needed for game object list and other things
#include <functional> // needed by thread class

#ifndef DEFAULT_NEAR_CULL_DISTANCE
#define DEFAULT_NEAR_CULL_DISTANCE 0.01 // Default near cull distance
#endif
#ifndef DEFAULT_FAR_CULL_DISTANCE
#define DEFAULT_FAR_CULL_DISTANCE 50000.0 // Default far cull distance
#endif

#define WORLD_SIZE 100 // This is a global that defines how large the world will be.
#define BLOCK_SIZE 1   // Default Block size. Changing this variable will affect the size of all blocks.

#define NUM_FRAMES 3          // Number of frames (rectangles) for the button sprite texture
#define MAP_RESOLUTION 512    // width and height of heightmap
#define CLIP_SHADERS_COUNT 1  // number of shaders that use a clipPlane
#define TREE_TEXTURE_COUNT 19 // number of textures for a tree
#define TREE_COUNT 8190       // number of tree billboards

#define MAX_INSTANCES 10000 // Max amount of objects.

#define MAX_WINDOW_TITLE_LENGTH 50

// alternative cases. makes it so that you dont have to write as much boiler plate
#define FILTER_BILINEAR TEXTURE_FILTER_BILINEAR
#define WRAP_CLAMP TEXTURE_WRAP_CLAMP

#define UNIFORM_VEC4 SHADER_UNIFORM_VEC4
#define UNIFORM_VEC3 SHADER_UNIFORM_VEC3
#define UNIFORM_INT SHADER_UNIFORM_INT
#define UNIFORM_FLOAT SHADER_UNIFORM_FLOAT
#define MAP_CUBEMAP SHADER_LOC_MAP_CUBEMAP
#define MAP_IRRADIANCE SHADER_LOC_MAP_IRRADIANCE
#define LOC_VECTOR_VIEW LOC_VECTOR_VIEW // TODO : Check if this is nessisary.
#define LOG_WARN LOG_WARNING // just to make typing easier.

#define DESPAWN_DISTANCE 1000.0f

#define MAX_SHADERS 10

#ifndef AUTHOR
#define AUTHOR MutedTea
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif


#define GRAVITATIONAL_CONSTANT 9.81f // m/s to comply with standard science units, this is basically the standard unit for acceleration.

// Plain structures in C++ (without constructors) can be initialized with { }
#if defined(__cplusplus)
#define CLITERAL(type) type
#else
#define CLITERAL(type) (type)
#endif

namespace Global
{

    using namespace Global;

    /*
    class Time
    {
    public:
        static inline double GetGameTimeFormatted()
        {
            return Global::Time::timeCounter;
        }

        static inline double GetGameTime()
        {
            return GetTime();
        }

        static inline void StartClock()
        {
            previousTime = GetTime();
            currentTime = 0.0;
            updateDrawTime = 0.0;
            waitTime = 0.0;
            deltaTime = 0.0f;
            timeCounter = 0.0f;
            targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());

            if (targetFPS == 0)
            {
                throw std::runtime_error("Target FPS must be greater than 0");
            }
        }

        // updates the clock
        static inline void Update()
        {
            currentTime = GetTime();
            updateDrawTime = currentTime - previousTime;

    
            if (targetFPS > 0)
            {
                waitTime = (1.0f / static_cast<float>(targetFPS)) - updateDrawTime;
                if (waitTime > 0.0)
                {
                    WaitTime(waitTime);
                    currentTime = GetTime();
                    deltaTime = static_cast<float>(currentTime - previousTime);
                }
            }
            else
            {
                deltaTime = static_cast<float>(updateDrawTime);
            }
            previousTime = currentTime;
        }

        static inline float DeltaTime()
        {
            return deltaTime;
        }

    private:
        static inline double previousTime;
        static inline double currentTime;
        static inline double updateDrawTime;
        static inline double waitTime;
        static inline float deltaTime;
        static inline float timeCounter;
        static inline int targetFPS;
    };*/
    
    
    class Tag {
        public:
            std::string Tag;  
            static inline std::string Translate(const char *tag) {
                std::string temp = tag;
                return temp;
            }   
    };  

    class MeshTools
    {
    public:
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

        typedef struct
        {
            Vector3 v1;
            Vector3 v2;
            Vector3 v3;
        } TriVert;

        /**
         * Returns a CubeVerticies object with all values set to zero.
         *
         * @return A CubeVerticies object with all values set to zero.
         */
        static MeshTools::CubeVerticies CVertZero()
        {
            return CubeVerticies{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        }

        static TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format)
        {
            TextureCubemap cubemap = {0};

            rlDisableBackfaceCulling(); // Disable backface culling to render inside the
                                        // cube

            // STEP 1: Setup framebuffer
            //------------------------------------------------------------------------------------------
            unsigned int rbo = rlLoadTextureDepth(size, size, true);
            cubemap.id = rlLoadTextureCubemap(0, size, format);

            unsigned int fbo = rlLoadFramebuffer(size, size);
            rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER,
                                0);
            rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0,
                                RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

            // Check if framebuffer is complete with attachments (valid)
            if (rlFramebufferComplete(fbo))
                TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully",
                         fbo);
            //------------------------------------------------------------------------------------------

            // STEP 2: Draw to framebuffer
            //------------------------------------------------------------------------------------------
            // NOTE: Shader is used to convert HDR equirectangular environment map to
            // cubemap equivalent (6 faces)
            rlEnableShader(shader.id);

            // Define projection matrix and send it to shader
            Matrix matFboProjection = MatrixPerspective(
                90.0 * DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
            rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION],
                               matFboProjection);
            
            // Define view matrix for every side of the cubemap
            Matrix fboViews[6] = {
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{1.0f, 0.0f, 0.0f},
                             Vector3{0.0f, -1.0f, 0.0f}),
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{-1.0f, 0.0f, 0.0f},
                             Vector3{0.0f, -1.0f, 0.0f}),
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f},
                             Vector3{0.0f, 0.0f, 1.0f}),
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, -1.0f, 0.0f},
                             Vector3{0.0f, 0.0f, -1.0f}),
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 1.0f},
                             Vector3{0.0f, -1.0f, 0.0f}),
                MatrixLookAt(Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, -1.0f},
                             Vector3{0.0f, -1.0f, 0.0f})};

            rlViewport(0, 0, size, size); // Set viewport to current fbo dimensions

            // Activate and enable texture for drawing to cubemap faces
            rlActiveTextureSlot(0);
            rlEnableTexture(panorama.id);

            for (int i = 0; i < 6; i++)
            {
                // Set the view matrix for the current cube face
                rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

                // Select the current cubemap face attachment for the fbo
                // WARNING: This function by default enables->attach->disables fbo!!!
                rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0,
                                    RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
                rlEnableFramebuffer(fbo);

                // Load and draw a cube, it uses the current enabled texture
                rlClearScreenBuffers();
                rlLoadDrawCube();

                // ALTERNATIVE: Try to use internal batch system to draw the cube instead of
                // rlLoadDrawCube for some reason this method does not work, maybe due to
                // cube triangles definition? normals pointing out?
                // TODO: Investigate this issue...
                // rlSetTexture(panorama.id); // WARNING: It must be called after enabling
                // current framebuffer if using internal batch system!
                // rlClearScreenBuffers();
                // DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
                // rlDrawRenderBatchActive();
            }
            //------------------------------------------------------------------------------------------

            // STEP 3: Unload framebuffer and reset state
            //------------------------------------------------------------------------------------------
            rlDisableShader();        // Unbind shader
            rlDisableTexture();       // Unbind texture
            rlDisableFramebuffer();   // Unbind framebuffer
            rlUnloadFramebuffer(fbo); // Unload framebuffer (and automatically attached
                                      // depth texture/renderbuffer)

            // Reset viewport dimensions to default
            rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
            rlEnableBackfaceCulling();
            //------------------------------------------------------------------------------------------

            cubemap.width = size;
            cubemap.height = size;
            cubemap.mipmaps = 1;
            cubemap.format = format;

            return cubemap;
        }

        /**
         * Generates a custom mesh based on the given vertices.
         *
         * @param verts the input vertices
         *
         * @return the generated mesh
         *
         * @throws ErrorType a description of any errors that may occur
         */
        static Mesh GenMeshCustom(TriVert verts)
        {
            Mesh mesh = {0};
            mesh.triangleCount = 1;
            mesh.vertexCount = mesh.triangleCount * 3;
            mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));  // 3 vertices, 3 coordinates each (x, y, z)
            mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float)); // 3 vertices, 2 coordinates each (x, y)
            mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));   // 3 vertices, 3 coordinates each (x, y, z)

            // Vertex at (0, 0, 0)
            mesh.vertices[0] = verts.v1.x;
            mesh.vertices[1] = verts.v2.x;
            mesh.vertices[2] = verts.v3.x;
            mesh.normals[0] = verts.v1.x;
            mesh.normals[1] = verts.v2.x;
            mesh.normals[2] = verts.v3.x;
            mesh.texcoords[0] = 0;
            mesh.texcoords[1] = 0;

            // Vertex at (1, 0, 2)
            mesh.vertices[3] = verts.v1.y;
            mesh.vertices[4] = verts.v2.y;
            mesh.vertices[5] = verts.v3.y;
            mesh.normals[3] = verts.v1.y;
            mesh.normals[4] = verts.v2.y;
            mesh.normals[5] = verts.v3.y;
            mesh.texcoords[2] = 0.5f;
            mesh.texcoords[3] = 1.0f;

            // Vertex at (2, 0, 0)
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

        /*
         */
    };
    class Math
    {

    private:
        // Stores what the last position generated was.
        static float LastPositiveXPos;
        static float LastPositiveZPos;

        static float LastNegativeXPos;
        static float LastNegativeZPos;

        // When the game starts, it is set to true because it is. this just is for use
        // within the terrain generator. I wouldnt touch.
        static bool isInitialX;
        static bool isInitialZ;

    public:
        static float randomRange(float min, float max)
        {
            return min + static_cast<float>(rand()) /
                             (static_cast<float>(RAND_MAX / (max - min)));
        }

        /*
                static int DoRoll(int Num1, int Num2)
                {
                    while (true)
                    {
                        int Roll1 = GetRandomValue(Num1, Num1 + Num2);
                        int Roll2 = GetRandomValue(Num1, Num1 + Num2);

                        if (Roll1 > Roll2)
                        {
                            return POSITIVE;
                        }
                        else if (Roll1 < Roll2)
                        {
                            return NEGATIVE;
                        }
                    }
                }

                static float createX(float CubePosX, ValueFlags flag)
                {
                    if (flag == POSITIVE)
                    {

                        if (isInitialX == true)
                        {
                            isInitialX = false;

                            LastPositiveXPos = BLOCK_SIZE;
                            CubePosX = LastPositiveXPos + BLOCK_SIZE;
                            return CubePosX;
                        }
                        else if (isInitialX == false)
                        {
                            CubePosX = LastPositiveXPos + BLOCK_SIZE;
                            LastPositiveXPos = CubePosX;
                            // adds together so that way cubes dont spawn in the same spot
                            return CubePosX;
                        }
                    }
                    else if (flag == NEGATIVE)
                    {
                        if (isInitialX == true)
                        {
                            isInitialX = false;
                            LastNegativeXPos = BLOCK_SIZE;
                            CubePosX = LastNegativeXPos;
                            return CubePosX;
                        }
                        else if (isInitialX == false)
                        {
                            CubePosX = LastNegativeXPos - BLOCK_SIZE;
                            LastNegativeXPos = CubePosX;
                            // adds together so that way cubes dont spawn in the same spot
                            return CubePosX;
                        }
                    }

                    return 1;
                }

                static float createY(float CubePosY)
                {

                    int lastY = CubePosY;

                    int rollResult = DoRoll(lastY, BLOCK_SIZE);

                    if (rollResult == NEGATIVE)
                    {
                        int Y = GetRandomValue(lastY, lastY - BLOCK_SIZE);

                        // Testing Phase
                        if (Y == lastY)
                        {
                        }
                        else if (Y != lastY)
                        {
                            CubePosY = Y;

                            return CubePosY;
                        }
                    }
                    else if (rollResult == POSITIVE)
                    {
                        int Y = GetRandomValue(lastY, lastY + BLOCK_SIZE);

                        // Testing Phase
                        if (Y == lastY)
                        {
                        }
                        else if (Y != lastY)
                        {
                            CubePosY = Y;

                            return CubePosY;
                        }
                    }
                    return 1;
                }

                static float createZ(float CubePosZ, ValueFlags flag)
                {
                    if (flag == POSITIVE)
                    {
                        if (isInitialZ == true)
                        {
                            isInitialZ = false;

                            LastPositiveZPos = BLOCK_SIZE;
                            CubePosZ = LastPositiveZPos + BLOCK_SIZE;
                            return CubePosZ;
                        }
                        else if (isInitialZ == false)
                        {
                            CubePosZ = LastPositiveZPos + BLOCK_SIZE;
                            LastPositiveZPos = CubePosZ;
                            // adds together so that way cubes dont spawn in the same spot
                            return CubePosZ;
                        }
                    }
                    else if (flag == NEGATIVE)
                    {
                        if (isInitialZ == true)
                        {
                            isInitialZ = false;
                            LastNegativeZPos = BLOCK_SIZE;
                            CubePosZ = LastNegativeZPos;
                            return CubePosZ;
                        }
                        else if (isInitialZ == false)
                        {
                            CubePosZ = LastNegativeXPos - BLOCK_SIZE;
                            LastNegativeZPos = CubePosZ;
                            // adds together so that way cubes dont spawn in the same spot
                            return CubePosZ;
                        }
                    }
                    return 1;
                }

        */

        static bool CheckCollisionRayBox(Ray ray, BoundingBox box, float *outDistance)
        {
            // Compute the inverse of the ray direction
            Vector3 invDir = {1.0f / ray.direction.x, 1.0f / ray.direction.y,
                              1.0f / ray.direction.z};

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
        static Vector3 CameraToWorld(Camera3D camera)
        {
            float distance;
            // Calculate the ray from the camera to the mouse position
            Vector2 mousePos = GetMousePosition();
            Vector3 mousePos3 = {mousePos.x, mousePos.y, 0};
            // Get the direction vector of the ray
            Vector3 rayDirection =
                Vector3Normalize(Vector3Subtract(mousePos3, camera.position));

            // Multiply the direction vector with a scalar value to increase the length of
            // the ray
            float rayLength = 40.0f;
            rayDirection = Vector3Scale(rayDirection, rayLength);

            // Create the ray with the modified direction
            Ray ray = {camera.position, rayDirection};

            // Calculate the distance from the camera to the ground plane
            distance = -(camera.position.y / ray.position.y);

            // Calculate the point where the ray intersects the ground plane
            Vector3 groundPoint =
                Vector3Add(camera.position, Vector3Scale(ray.position, distance));

            return groundPoint;
        }

        typedef enum
        {
            NEGATIVE = 0,
            POSITIVE = 1
        } ValueFlags;
        /**
         * Calculates the mean of a given vector of float values.
         *
         * @param data the vector containing the float values for which the mean needs to be calculated.
         *
         * @return the mean value of the input vector.
         *
         * @throws None
         */
        static float Mean(const std::vector<float> &data)
        {
            float result = 0.0;
            for (unsigned int i = 1; i < data.size(); i++)
            {
                result += data[i - 1] + data[i];
            }
            return result / data.size();
        }

        /**
         * Inverts the given float value.
         *
         * @param Value the float value to be inverted
         *
         * @return the inverted float value
         *
         * @throws ErrorType description of error
         */
        static float Invert(float Value)
        {
            return -Value;
        }

        static Vector3 Vector3Random(int min, int max)
        {
            return Vector3{static_cast<float>(GetRandomValue(min, max)),
                             static_cast<float>(GetRandomValue(min, max)),
                             static_cast<float>(GetRandomValue(min, max))};
        }

        // zeros cube verticies
        // rounds vector3
        static Vector3 RoundVec3(Vector3 Target)
        {
            return Vector3{
                (float)round(Target.x), (float)round(Target.y), (float)round(Target.z)};
        }

        // checks if vector3 is negative
        // returns vector on for both positive and negative
        static Vector3 Vector3MaxPos()
        {
            return Vector3{WORLD_SIZE, WORLD_SIZE, WORLD_SIZE};
        }

        // return the average of a floating point data set

        static Vector3 Vector3RandomControlled(Vector3 start, int minDeviation, int maxDeviation)
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

        // same as DualVector3RandomEx() but only returns one value
        static Vector3 Vector3RandomEx(Vector3 min, Vector3 max)
        {
            return Vector3{(float)GetRandomValue(min.x, max.x), (float)GetRandomValue(min.y, max.y), (float)GetRandomValue(min.z, max.z)};
        }
    };

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

    static const BoundingBox BoxNull = {0, 0, 0, 0, 0, 0};
}
