/*******************************************************************************************
*
*   raylib very basic lighting example
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   This example Copyright (c) 2018 Chris Camacho (codifies) http://bedroomcoders.co.uk/captcha/
*
* THIS EXAMPLE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* This example may be freely redistributed.
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

/*
 *
 * This example show the bare minimum needed show a lit model
 *
 */

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(1280, 720, "raylib [models] example - simple lighting material");

    // Define the camera to look into our 3d world
    Camera camera = {(Vector3){ 0.0f, 1.0f, 2.0f }, (Vector3){ 0.0f, 0.0f, 0.0f },
                        (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE};

    // Load model
    Model model = LoadModelFromMesh(GenMeshSphere(.5,32,32));

    // texture the model
    Texture texture = LoadTexture("data/test.png");
    model.materials[0].maps[MAP_DIFFUSE].texture = texture;

    Shader shader = LoadShader("data/simpleLight.vs", "data/simpleLight.fs");
    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // ambient light level
    int amb = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, amb, (float[4]){0.2,0.2,0.2,1.0}, UNIFORM_VEC4);

    // set the models shader
    model.materials[0].shader = shader;

    // make a light
    Light light = CreateLight(LIGHT_POINT, (Vector3){ 2,2,0 }, Vector3Zero(), WHITE, shader);
    (void)light; // honest I'm using that variable !!! (unused variable warning)

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop

    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        UpdateCamera(&camera);              // Update camera

        // update the light shader with the camera view position
        SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &camera.position.x, UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

                // draw the three models
                DrawModel(model, Vector3Zero(), 1.0f, WHITE);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);         // Unload the model
    UnloadTexture(texture);     // Unload the texture
    UnloadShader(shader);

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

