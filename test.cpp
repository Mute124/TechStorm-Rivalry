/*******************************************************************************************
 *
 *   raylib [shaders] example - Apply a postprocessing shader and connect a custom uniform variable
 *
 *   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
 *         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
 *
 *   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
 *         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
 *         raylib comes with shaders ready for both versions, check raylib/shaders install folder
 *
 *   Example originally created with raylib 1.3, last time updated with raylib 4.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2015-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

/*******************************************************************************************
*
*   raylib [shaders] example - basic lighting
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 3.0, last time updated with raylib 4.2
*
*   Example contributed by Chris Camacho (@codifies) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2023 Chris Camacho (@codifies) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

/*******************************************************************************************
*
*   raylib [shaders] example - Raymarching shapes generation
*
*   NOTE: This example requires raylib OpenGL 3.3 for shaders support and only #version 330
*         is currently supported. OpenGL ES 2.0 platforms are not supported at the moment.
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Classes/lib/raylib.h"
#include "Classes/lib/rlgl.h"
#include "Classes/lib/raymath.h"
#include <math.h>
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB -> Not supported at this moment
    #define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------------
// Declare custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
static RenderTexture2D LoadRenderTextureDepthTex(int width, int height);
// Unload render texture from GPU memory (VRAM)
static void UnloadRenderTextureDepthTex(RenderTexture2D target);

//------------------------------------------------------------------------------------
// Declare custom Structs
//------------------------------------------------------------------------------------

typedef struct {
    unsigned int camPos, camDir, screenCenter;
}RayLocs ;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - write depth buffer");

    // This Shader calculates pixel depth and color using raymarch
    Shader shdrRaymarch = LoadShader(0, TextFormat("resources/shaders/glsl330/hybrid_raymarch.fs", GLSL_VERSION));

    // This Shader is a standard rasterization fragment shader with the addition of depth writing
    // You are required to write depth for all shaders if one shader does it
    Shader shdrRaster = LoadShader(0, TextFormat("resources/shaders/glsl330/hybrid_raster.fs", GLSL_VERSION));

    // Declare Struct used to store camera locs.
    RayLocs marchLocs = {0};

    // Fill the struct with shader locs.
    marchLocs.camPos = GetShaderLocation(shdrRaymarch, "camPos");
    marchLocs.camDir = GetShaderLocation(shdrRaymarch, "camDir");
    marchLocs.screenCenter = GetShaderLocation(shdrRaymarch, "screenCenter");

    // Transfer screenCenter position to shader. Which is used to calculate ray direction. 
    Vector2 screenCenter = {screenCenter.x = screenWidth/2.0, screenCenter.y = screenHeight/2.0};
    SetShaderValue(shdrRaymarch, marchLocs.screenCenter , &screenCenter , SHADER_UNIFORM_VEC2);

    // Use Customized function to create writable depth texture buffer
    RenderTexture2D target = LoadRenderTextureDepthTex(screenWidth, screenHeight);

    // Define the camera to look into our 3d world
    Camera camera = {
        .position = (Vector3){ 0.5f, 1.0f, 1.5f },    // Camera position
        .target = (Vector3){ 0.0f, 0.5f, 0.0f },      // Camera looking at point
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
        .fovy = 45.0f,                                // Camera field-of-view Y
        .projection = CAMERA_PERSPECTIVE              // Camera projection type
    };
    
    // Camera FOV is pre-calculated in the camera Distance.
    double camDist = 1.0/(tan(camera.fovy*0.5*DEG2RAD));
    
    Mesh mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model model = LoadModelFromMesh(mesh);

   model.materials[0].shader = shdrRaymarch;
    //--------------------------------------------------------------------------------------
    DisableCursor();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Update Camera Postion in the ray march shader.
        SetShaderValue(shdrRaymarch, marchLocs.camPos, &(camera.position), RL_SHADER_UNIFORM_VEC3);
        
        // Update Camera Looking Vector. Vector length determines FOV.
        Vector3 camDir = Vector3Scale( Vector3Normalize( Vector3Subtract(camera.target, camera.position)) , camDist);
        SetShaderValue(shdrRaymarch, marchLocs.camDir, &(camDir), RL_SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        // Draw into our custom render texture (framebuffer)
        BeginTextureMode(target);
            ClearBackground(WHITE);

            // Raymarch Scene
            rlEnableDepthTest(); //Manually enable Depth Test to handle multiple rendering methods.
            BeginShaderMode(shdrRaymarch);
            DrawModel(model, camera.target, 1.0f, GRAY);
                DrawRectangleRec((Rectangle){0,0,screenWidth,screenHeight},WHITE);
                
                
            EndShaderMode();


            
            
            
            


            // Raserize Scene
            BeginMode3D(camera);
                BeginShaderMode(shdrRaster);
                    DrawModel(model, camera.target, 1.0f, GRAY);
                    DrawCubeWiresV((Vector3){ 0.0f, 0.5f, 1.0f }, (Vector3){ 1.0f, 1.0f, 1.0f }, RED);
                    DrawCubeV((Vector3){ 0.0f, 0.5f, 1.0f }, (Vector3){ 1.0f, 1.0f, 1.0f }, PURPLE);
                    DrawCubeWiresV((Vector3){ 0.0f, 0.5f, -1.0f }, (Vector3){ 1.0f, 1.0f, 1.0f }, DARKGREEN);
                    DrawCubeV((Vector3) { 0.0f, 0.5f, -1.0f }, (Vector3){ 1.0f, 1.0f, 1.0f }, YELLOW);
                    DrawGrid(10, 1.0f);
                    
                EndShaderMode();
            EndMode3D();
        EndTextureMode();

        // Draw into screen our custom render texture 
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            DrawTextureRec(target.texture, (Rectangle) { 0, 0, screenWidth, -screenHeight }, (Vector2) { 0, 0 }, WHITE);
            
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTextureDepthTex(target);
    UnloadShader(shdrRaymarch);
    UnloadShader(shdrRaster);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Define custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
RenderTexture2D LoadRenderTextureDepthTex(int width, int height)
{
    RenderTexture2D target = { 0 };

    target.id = rlLoadFramebuffer(width, height);   // Load an empty framebuffer

    if (target.id > 0)
    {
        rlEnableFramebuffer(target.id);

        // Create color texture (default to RGBA)
        target.texture.id = rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        target.texture.width = width;
        target.texture.height = height;
        target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        target.texture.mipmaps = 1;

        // Create depth texture buffer (instead of raylib default renderbuffer)
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach color texture and depth texture to FBO
        rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    }
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload render texture from GPU memory (VRAM)
void UnloadRenderTextureDepthTex(RenderTexture2D target)
{
    if (target.id > 0)
    {
        // Color texture attached to FBO is deleted
        rlUnloadTexture(target.texture.id);
        rlUnloadTexture(target.depth.id);

        // NOTE: Depth texture is automatically
        // queried and deleted before deleting framebuffer
        rlUnloadFramebuffer(target.id);
    }
}



/*

#include "Classes/lib/raylib.h"

#include "Classes/lib/raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "Classes/lib/rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - custom uniform variable");

    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = (Vector3){8.0f, 8.0f, 8.0f}; // Camera position
    camera.target = (Vector3){0.0f, 1.5f, 0.0f};   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera projection type

    Model model = LoadModel("resources/models/barracks.obj");                 // Load OBJ model
    Texture2D texture = LoadTexture("resources/models/barracks_diffuse.png"); // Load model texture (diffuse map)
    Texture2D occ = LoadTexture("resources/textures/occlusiontest_occlusion.png");
    
    
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set model diffuse texture
    
    model.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture = occ;
    model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;



    Vector3 position = {0.0f, 0.0f, 0.0f}; // Set model position

    // Load postprocessing shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    Shader shader = LoadShader(TextFormat("resources/shaders/lighting.vs", GLSL_VERSION),
                               TextFormat("resources/shaders/lighting.fs", GLSL_VERSION));

    // Get variable (uniform) location on the shader to connect with the program
    // NOTE: If uniform variable could not be found in the shader, function returns -1
    int swirlCenterLoc = GetShaderLocation(shader, "center");

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

    float swirlCenter[2] = {(float)screenWidth / 2, (float)screenHeight / 2};
    
    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");

    static const float a[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    SetShaderValue(shader, ambientLoc, &a, SHADER_UNIFORM_VEC4);

    // Create a RenderTexture2D to be used for render to texture
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

  
    //--------------------------------------------------------------------------------------
    model.materials->shader = shader;

    
    
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        Vector2 mousePosition = GetMousePosition();

        swirlCenter[0] = mousePosition.x;
        swirlCenter[1] = screenHeight - mousePosition.y;

        // Send new value to the shader to be used on drawing
        SetShaderValue(shader, swirlCenterLoc, swirlCenter, SHADER_UNIFORM_VEC2);
        //----------------------------------------------------------------------------------
        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);  // Enable drawing to texture
        ClearBackground(RAYWHITE); // Clear texture background

        BeginMode3D(camera);                     // Begin 3d mode drawing
        DrawModel(model, position, 0.5f, WHITE); // Draw 3d model with texture
        DrawGrid(10, 1.0f);                      // Draw a grid
        EndMode3D();                             // End 3d mode drawing, returns to orthographic 2d mode

        DrawText("TEXT DRAWN IN RENDER TEXTURE", 200, 10, 30, RED);
        EndTextureMode(); // End drawing to texture (now we have a texture available for next passes)

        BeginDrawing();
        ClearBackground(RAYWHITE); // Clear screen background

        // Enable shader using the custom uniform
        BeginShaderMode(shader);
        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Vector2){0, 0}, WHITE);
        EndShaderMode();

        // Draw some 2d text over drawn texture
        DrawText("(c) Barracks 3D model by Alberto Cano", screenWidth - 220, screenHeight - 20, 10, GRAY);
        DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);        // Unload shader
    UnloadTexture(texture);      // Unload texture
    UnloadModel(model);          // Unload model
    UnloadRenderTexture(target); // Unload render texture

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
*/
