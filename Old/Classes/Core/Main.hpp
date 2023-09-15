#pragma once
#include "Game.hpp"

#include "../lib/Buttons/src/ButtonR.h" // Needed for buttons.
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "../lib/rcamera.h"
#include "../lib/rlgl.h"

// Object ..
#include "../Monobehavior.h"
#include "../Block.h"

#include "../GUtils.h"
#include "../Gameobj.h"
#include "../Globals.h"
#include "../Screens/MenuCamera.h"
#include "../Player/Player.h"
#include "../TestPlane.h"
#include "../Logging/Logman.hpp"
#include "../Vehicles/Plane.h"
#include "../World/WorldFloor.h"

#include "../HeightMap.h"
#include "../Flashlight.h"
#include "../Gun.h"
#include "../Metal_Block.h"
#include "../World/Sun.hpp"

#include "Window.hpp"
#include "GameScreen.h"
// Core Includes
#include "GameScreen.h"

// Externs required for functionality
// In the lib file
// #include "../../lib/external/glfw/deps/glad/gl.h"

// default libs
#include <algorithm> // needed for Find()
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> // needed for game object list
#include <thread>
#include <future>

#include <fstream>
#include <iostream>

#define RLIGHTS_IMPLEMENTATION
#include "../lib/rlights.h"

// Main Logic goes here. This is where most of the actions will be.



struct SunData
{
    Light DirectionalLight;
    Light AmbientLight;
    Vector3 Position;
    Vector3 Target;

    bool isEnabled;
};

class Sun
{
public:
    Sun(Vector3 position, Vector3 target, Color color, bool isenabled)
    {
        data.DirectionalLight = CreateLight(LIGHT_DIRECTIONAL, position, target, color, Main::postProcessShader);
        data.AmbientLight = CreateLight(LIGHT_POINT, position, target, color, Main::postProcessShader);
        data.Position = position;
        data.Target = target;
        data.isEnabled = isenabled;

        Vector3 lightDirection[3] = {
            this->data.Target, this->data.AmbientLight.target}; // Example light direction pointing upwards
        SetShaderValue(Main::postProcessShader, this->data.DirectionalLight.targetLoc, &lightDirection[0],
                       SHADER_UNIFORM_VEC3);
        SetShaderValue(Main::postProcessShader, this->data.DirectionalLight.targetLoc, &lightDirection[1],
                       SHADER_UNIFORM_VEC3);
        // SetShaderValue(Main::postProcessShader, flashlight->GetLight().targetLoc, &lightDirection[1],
        //                SHADER_UNIFORM_VEC3);
    };

    void DisableLight()
    {
        data.isEnabled = false;
    }

    void EnableLight()
    {
        data.isEnabled = true;
    }
    SunData data;
};



class Main
{
public:
static inline Sun *sun = new Sun((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, WHITE, true);

    Main()
    {
        InitializeGameVariables();
        InnitShaders();
        CreateStandardClasses();
        CreateSkybox();
        Logman::CustomLog(LOG_INFO, "Game Initialized", NULL);
        StartGameLoop();
    }

    /**
     * Initializes the game variables.
     *
     * @param None
     *
     * @return None
     *
     * @throws None
     */
    void InitializeGameVariables()
    {
        InitAudioDevice(); // starts the audio driver(s).

        DisableEventWaiting(); // Enables the ability for the game to run even if a
                               // thing is lagging. Like for example if terrain is
                               // still generating, it wont pause the game.

        // SetTargetFPS(this->targetFPS); // Set our game to run at 60 frames-per-second
        SetExitKey(KEY_BACKSPACE); // In event of your fuck up press this.
    }

    /**
     * A description of the entire C++ function.
     *
     * @param paramName description of parameter
     *
     * @return description of return value
     *
     * @throws ErrorType description of error
     */
    void Run()
    {
    }

    // Close game normally
    void Close()
    {
        // TODO : Delete all pointers
    }

    // Immediatly exit now and force stop all actions.
    void ForceExit()
    {
    }

    // returns if the game is paused.
    bool isPaused() {}

    /**
     * Initializes the shaders.
     */
    static inline void InnitShaders()
    {
        // Set shader value: ambient light level
        int ambientLoc = GetShaderLocation(postProcessShader, "ambient");
        static const float ambientColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        SetShaderValue(postProcessShader, ambientLoc, ambientColor, SHADER_UNIFORM_VEC4);

        SetShaderValue(postProcessShader, postProcessShader.locs[SHADER_LOC_COLOR_AMBIENT], ambientColor, SHADER_UNIFORM_VEC4);

        postProcessShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(postProcessShader, "viewPos");

        postProcessShader.locs[SHADER_LOC_COLOR_AMBIENT] = GetShaderLocation(postProcessShader, "ambient");

        int PostViewLoc = GetShaderLocation(postProcessShader, "viewPos");
        postProcessShader.locs[SHADER_LOC_MATRIX_MODEL] =
            GetShaderLocation(postProcessShader, "matModel");

        Color skyColor = SKYBLUE;
        Color groundColor = GRAY;
        // ambient light level
        int amb = GetShaderLocation(postProcessShader, "ambient");
        static float shaderamb[4] = {5.0f, 5.0f, 5.0f, 5.0f};
        SetShaderValue(postProcessShader, amb, shaderamb, UNIFORM_VEC4);

        SetShaderValue(postProcessShader,
                       GetShaderLocation(postProcessShader, "skyColor"), &skyColor,
                       SHADER_UNIFORM_VEC4);
        SetShaderValue(postProcessShader,
                       GetShaderLocation(postProcessShader, "groundColor"),
                       &groundColor, SHADER_UNIFORM_VEC4);

        SetShaderValue(postProcessShader,
                       GetShaderLocation(postProcessShader, "ambientColor"), &amb,
                       SHADER_UNIFORM_VEC4);
    }

    // Creates the skybox.
    void CreateSkybox()
    {
        // Load skybox model
        // skybox creation.
        Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
        skybox = LoadModelFromMesh(cube);

        bool useHDR = true;

        // Load skybox shader and set required locations
        // NOTE: Some locations are automatically set at shader loading
        skybox.materials[0].shader =
            LoadShader("resources/skybox.vs", "resources/skybox.fs");

        // since the compiler complains about the references of such, these three vars
        // are for the skybox shaders. They will be deleted after.
        static int a = 7;
        static int b = {useHDR ? 1 : 0};
        static int c = 0;

        SetShaderValue(
            skybox.materials[0].shader,
            GetShaderLocation(skybox.materials[0].shader, "environmentMap"), &a,
            SHADER_UNIFORM_INT);
        SetShaderValue(skybox.materials[0].shader,
                       GetShaderLocation(skybox.materials[0].shader, "doGamma"), &b,
                       SHADER_UNIFORM_INT);
        SetShaderValue(skybox.materials[0].shader,
                       GetShaderLocation(skybox.materials[0].shader, "vflipped"), &b,
                       SHADER_UNIFORM_INT);

        // Load cubemap shader and setup required shader locations
        Shader shdrCubemap =
            LoadShader("resources/cubemap.vs", "resources/cubemap.fs");

        SetShaderValue(shdrCubemap,
                       GetShaderLocation(shdrCubemap, "equirectangularMap"), &c,
                       SHADER_UNIFORM_INT);

        char skyboxFileName[256] = {0};

        Texture2D panorama;

        if (useHDR)
        {
            TextCopy(skyboxFileName, "resources/daytime.hdr");

            // Load HDR panorama (sphere) texture
            panorama = LoadTexture(skyboxFileName);

            // Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR
            // texture NOTE 1: New texture is generated rendering to texture, shader
            // calculates the sphere->cube coordinates mapping NOTE 2: It seems on some
            // Android devices WebGL, fbo does not properly support a FLOAT-based
            // attachment, despite texture can be successfully created.. so using
            // PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of
            // PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
            skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = Global::MeshTools::GenTextureCubemap(
                shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

            UnloadTexture(panorama); // Texture not required anymore, cubemap
                                     // already generated
        }
        else
        {
            Image img = LoadImage("resources/skybox.png");
            skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
                img, CUBEMAP_LAYOUT_AUTO_DETECT); // CUBEMAP_LAYOUT_PANORAMA
            UnloadImage(img);
        }
    }

    /**
     * Creates standard classes.
     *
     * @param None
     *
     * @return None
     *
     * @throws None
     */
    void CreateStandardClasses()
    {
        Model DefaultBlockModel = LoadModelFromMesh(GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)); // this is the default model used in blocks.

        // Player Object Creation
        const int Playersize = 3.f;
        Model PlayerModel = LoadModelFromMesh(GenMeshCube(3.0f, 3.0f, 3.0f)); // Generates the playermodel. For right now it is a cube.

        // function for other details. It is in Player.h
        // Adds the player obj to the list of Game objects so it gets freed and drawn
        // automatically. Neat aint it :)
        player = new Player(Vector3{0.0f, 2.0f, 4.0f}, 100, PlayerModel, CAMERA_FIRST_PERSON); // Player object creation, Read the Player()
        player->model.materials[0].shader = postProcessShader;

        float angle = 6.282f;
        float radius = 100.0f;

        GameObject::PushObject(player);
    }

    void StartGameLoop()
    {
        while (!WindowShouldClose())
        {

            // Pause Menu
            if (IsKeyPressed(KEY_ESCAPE))
            {
                // Todo, move the menuCamera to be created on game startup and then hidden. it gets shown on if statement validation
                bool exit = false;
                bool manualExit = false;

                MenuCameraComponent *men_pause = new MenuCameraComponent();
                ButtonR *save = new ButtonR("Save", 100, 100);
                ButtonR *Options = new ButtonR("Options", 100, 200);
                ButtonR *exitButton = new ButtonR("Exit to Windows", 100, 300);

                int cycle; // not used rn
                EnableCursor();
                while (!exit)
                {
                    BeginDrawing();
                    DrawText("PAUSE", 100, 100, 20, RED);
                    save->draw();
                    save->update();

                    Options->draw();
                    Options->update();

                    exitButton->draw();
                    exitButton->update();
                    if (save->IsClicked())
                    {

                        // todo : implement Saving game data, probably use the Objects vector.
                    }

                    if (exitButton->IsClicked())
                    {
                        manualExit = true;
                    }

                    if (Options->IsClicked())
                    {
                        bool closeOptions = false;
                        while (!closeOptions)
                        {
                            // TODO : Add options

                            if (IsKeyDown(KEY_ESCAPE))
                            {
                                closeOptions = true;
                            }
                        }
                    }

                    EndDrawing();
                    if (IsKeyPressed(KEY_ESCAPE) && exit == false)
                    {
                        exit = true;
                    }
                    else if (IsKeyPressed(KEY_ESCAPE) && exit == true)
                    {
                        break;
                    }

                    if (manualExit)
                    {
                        exit = true;
                    }
                }
                // cleanup
                UnloadTexture(tex);
                delete men_pause;
                delete save;
                delete exitButton;
                if (manualExit)
                {

                    Logman::CustomLog(LOG_INFO, "Exiting Game", NULL);
                    break;
                }
            }

            // update ray
            ray.position = player->getPosition();
            ray.direction = player->getTarget();

            // to do :
            // Update variables that are declared in the settings.ini file

            UpdateCamera(
                player->getSelfCameraPointer(),
                player
                    ->cameraMode); // Updates the camera with the current mode and data.

            // Keybinds yah

            // Check for left click

            /*
                        if (IsKeyPressed(KEY_F))
                    {
                        flashlight->Switch();
                    }
            */

            // If statement for block placing.
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vector3 placepos;
                placepos.x = round(player->getTarget().x);
                placepos.y = round(player->getTarget().y);
                placepos.z = round(player->getTarget().z);

                GameObject::PushObject(new Block(BlockStone, placepos, WHITE, postProcessShader, Block::DefaultBlockModel));
            }

            if (!IsKeyDown(KEY_LEFT_ALT))
            {
                if (!IsCursorHidden())
                {
                    DisableCursor();
                }
                UpdateCamera(player->getSelfCameraPointer(), player->cameraMode); // Update camera
            }
            else
            {
                EnableCursor();
            }

            if (IsKeyPressed(KEY_F9))
            {
                // take a screenshot
                for (int i = 0; i < INT_MAX; i++)
                {
                    const char *fileName = TextFormat("screen%i.png", i);
                    // if there isnt a duplicate file, it then will create a screenshot.
                    if (FileExists(fileName) == 0)
                    {
                        TakeScreenshot(fileName);
                        break;
                    }
                }
            }

            //----------------------------------------------------------------------------------

            PollInputEvents(); // helps for some reason?

            // Update the light shader with the camera view position
            // Update the shader with the camera view vector (points towards { 0.0f,
            // 0.0f, 0.0f })

            float cameraPos[3] = {player->getPosition().x,
                                  player->getPosition().y,
                                  player->getPosition().z};

            Vector3 SunPos = {sun->data.Position.x, sun->data.Position.y, sun->data.Position.z};

            UpdateLightValues(postProcessShader, sun->data.DirectionalLight);
            UpdateLightValues(postProcessShader, sun->data.AmbientLight);

            // flashlight->Update(postProcessShader, player->getPosition(), player->getPosition());

            SetShaderValue(postProcessShader, postProcessShader.locs[SHADER_LOC_VECTOR_VIEW], &SunPos, SHADER_UNIFORM_VEC3);

            GameObject::Render();

            BeginTextureMode(this->target);

            ClearBackground(RAYWHITE);
            BeginMode3D(player->getSelfCamera());

            rlDisableBackfaceCulling();
            rlDisableDepthMask();
            DrawModel(skybox, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
            rlEnableBackfaceCulling();
            rlEnableDepthMask();

            // DrawModel(terrain, Vector3Zero(), 1.0f, RED); // not needed atm, if it isnt for a while, it will get deleted
            //  We are inside the cube, we need to disable backface culling!

            EndShaderMode();
            BeginShaderMode(postProcessShader);
            GameObject::Render();
            // Draw spheres to show where the lights are
            for (int i = 0; i < MAX_LIGHTS; i++)
            {
                if (sun->data.isEnabled)
                    DrawSphereEx(sun->data.Position, 0.2f, 8, 8, GREEN);
                else
                    DrawSphereWires(sun->data.Position, 0.2f, 8, 8,
                                    ColorAlpha(sun->data.AmbientLight.color, 0.3f));
            }

            // Get the mouse ray based on the current camera position and mouse position
            Vector2 mouse_pos = GetMousePosition();
            ray = GetMouseRay(mouse_pos, player->getSelfCamera());

            EndShaderMode();
            EndMode3D();

            EndTextureMode();

            BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextureRec(target.texture, (Rectangle){0, 0, GetScreenWidth(), -GetScreenHeight()}, Vector2Zero(), WHITE);
            EndDrawing();
        }
    }

    /**
     * Checks if the temporary data folder exists.
     *
     * @return true if the temporary folder exists, false otherwise
     */
    static inline bool DoesTempFolderExist()
    {
        return DirectoryExists("temp");
    }

    /**
     * Creates a folder at the specified path with the given name.
     *
     * @param path The path where the folder will be created.
     * @param Name The name of the folder to be created.
     *
     * @throws ErrorType If there is an error creating the folder.
     */
    static inline void CreateFolder(const char *path, const char *Name)
    {
        system(TextFormat("mkdir %s%s", path, Name));
    }

    /**
     * Deletes a folder at the specified path with the given name.
     *
     * @param path the path to the folder
     * @param Name the name of the folder
     *
     * @throws ErrorType description of error
     */
    static inline void DeleteFolder(const char *path, const char *Name)
    {
        system(TextFormat("rmdir /s /q %s%s", path, Name));
    }

    static inline Player GetPlayer() {}

    static inline RenderTexture2D target = LoadRenderTexture(Game::screenWidth, Game::screenHeight);

    static inline Shader postProcessShader = LoadShader(TextFormat("resources/shaders/glsl330/lighting.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl330/lighting.fs", GLSL_VERSION));

    Ray ray; // Player View Ray. used for block breaking : OUTDATED!
    static inline Player *player = nullptr;

    
    Model skybox;

private:
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Texture tex;
    double Starttime = GetTime();

    double current = GetTime();
    bool pause = false; // Pause control flag

    bool ShouldForceExit; // should the program force exit

    /**
     * Initializes the `logman` object by creating a new instance of the `Logman` class in the heap memory.
     *
     * @param None
     *
     * @return None
     *
     * @throws None
     */
    void InitLogman()
    {
        logman = new Logman(); // creates now logman instance in heap memory
    }

    Logman *logman; // Logman Declaration
};
