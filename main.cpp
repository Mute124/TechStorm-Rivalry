/*
  Minero Code. Common game startup (Ie. Engine shaders, player, etc) go into Game.h

  TODO :
    Work on graphics using the Erosion Standalone reference code.
    Move config arguments into TOML files.


*/

// Run Args
bool SkipMainMenu = true;

#include "lib/Buttons/src/ButtonR.h" // Needed for buttons.
// Raylib Framework
#include "lib/raylib.h"
#include "lib/raymath.h"
#include "lib/rcamera.h"
#include "lib/rlgl.h"

// Game Engine
#include "Engine/Classes/Project/Game/Game.h"
#include "Engine/DataSets/Globals.h"
#include "Engine/Classes/ShapeBase/Block/Block.h"
#include "Engine/Classes/GameObject/Gameobject.h"
#include "Engine/Classes/GUIs/Core/MenuCamera.h"
#include "Engine/Classes/Player/Player.h"
#include "Engine/Classes/Logging/Logman.h"
#include "Engine/Classes/ConfigMan/ConfigMan.h" // config manager
#include "Engine/Classes/GUIs/Console/Console.h"

// Minero Classes
#include "Minero/Classes/Vehicles/Plane.h"
// Externs required for functionality
// In the lib file
#include "lib/external/glfw/deps/glad/gl.h"

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
#include "lib/rlights.h"

// This translates the current screen
typedef enum
{
  Main = 0,
  PauseMenu,
  Gameplay

} GameScreen;

// This is a struct that is a utility for the terrain generator. Dont touch. It
// is mainly used within the GenX, Y, and Z funcs

// Get pixel data from image as a Color struct array // Generate GPU mipmaps for
// a texture Generate cubemap (6 faces) from equirectangular (panorama) texture

// gets the distance from the camera to well, the world

// Audio Functions
void PlayFootstepSound(void *data); // Plays a sound for footsteps

// Physics functions
bool CheckCollisionRayBox(Ray ray, BoundingBox box, float *outDistance);

// Custom Functions

// random float between two values

Ray ray; // Player View Ray. used for block breaking

// Custom timing variables

float position = 0.0f; // Circle position
bool pause = false;    // Pause control flag

int targetFPS = GetMonitorRefreshRate(GetCurrentMonitor()); // This is what is used to calculate DeltaTime and set target fps

int main(void)
{
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  Logman::CustomLog(LOG_INFO, "Log man Created. ", NULL);
  GameScreen currentScreen = Main;

  // These store the center X and Y. Vector2 didnt work for some reason, idk
  const int middlex = (screenWidth / 2);
  const int middley = (screenHeight / 2);

  Game *game = new Game();
  game->StartGame();
  // Game::Initialize();

  ButtonR *mmen_start = new ButtonR("start", (float)middlex, (float)middley); // Main start button

  MenuCamera *menucamera = new MenuCamera(); // camera for the main menu is needed due to dimension differences

  // Load postprocessing shader
  // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default
  // vertex shader

  //  std::vector<GameObject *>
  //      objects; // Declares the main list for all game objects. Do not touch or
  // bad things will happen. Like memory leaks :)

  Model DefaultBlockModel = LoadModelFromMesh(
      GenMeshCube(BLOCK_SIZE, BLOCK_SIZE,
                  BLOCK_SIZE)); // this is the default model used in blocksd.

  Shader postProcessShader = LoadShader(TextFormat("../../Minero-Game/resources/shaders/glsl330/lighting.vs", GLSL_VERSION), TextFormat("../../Minero-Game/resources/shaders/glsl330/lighting.fs", GLSL_VERSION));

  // Shader fog = LoadShader("resources/shaders/glsl330/lighting.vs", "resources/shaders/glsl330/fog.fs");

  // fog.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(fog, "matModel");
  // fog.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(fog, "viewPos");

  // float fogDensity = 1.0f;
  // int fogDensityLoc = GetShaderLocation(fog, "fogDensity");
  // SetShaderValue(fog, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);

  postProcessShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(postProcessShader, "viewPos");

  postProcessShader.locs[SHADER_LOC_COLOR_AMBIENT] = GetShaderLocation(postProcessShader, "ambient");

  // Set shader value: ambient light level
  int ambientLoc = GetShaderLocation(postProcessShader, "ambient");
  static const Color ambientColor = WHITE;
  SetShaderValue(postProcessShader, ambientLoc, &ambientColor, SHADER_UNIFORM_VEC4);

  SetShaderValue(postProcessShader, postProcessShader.locs[SHADER_LOC_COLOR_AMBIENT], &ambientColor, SHADER_UNIFORM_VEC4);
  // Player Object Creation
  const int Playersize = 3;
  Model PlayerModel = LoadModelFromMesh(GenMeshCube(3.0f, 3.0f, 3.0f)); // Generates the playermodel. For right now it is a cube.
  Player *player = new Player(Vector3{0.0f, 2.0f, 4.0f}, 100, PlayerModel, CAMERA_FIRST_PERSON);

  GameObject::PushObject(player);

  // Block Initialization

DefaultBlockModel.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = Global::MeshTools::GenTextureCubemap(
        postProcessShader, game->renderer->fbo.texture, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);


  Block *block = new Block(BlockDirt, Vector3Zero(), WHITE,
                           postProcessShader, DefaultBlockModel);

  GameObject::PushObject(block);

  int PostViewLoc = GetShaderLocation(postProcessShader, "viewPos"); // View pos shader location

  // Load skybox model
  // skybox creation.
  Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
  Model skybox = LoadModelFromMesh(cube);

  bool useHDR = true;

  // Load skybox shader and set required locations
  // NOTE: Some locations are automatically set at shader loading

  skybox.materials[0].shader = LoadShader("../../Minero-Game/resources/skybox.vs", "../../Minero-Game/resources/skybox.fs");

  // since the compiler complains about the references of such, these three vars
  // are for the skybox shaders. They will be deleted after.
  static int a = MATERIAL_MAP_CUBEMAP;
  static int b = {useHDR ? 1 : 0};
  static int c = {useHDR ? 1 : 0};

  SetShaderValue(
      skybox.materials[0].shader,
      GetShaderLocation(skybox.materials[0].shader, "environmentMap"), &a,
      SHADER_UNIFORM_INT);
  SetShaderValue(skybox.materials[0].shader,
                 GetShaderLocation(skybox.materials[0].shader, "doGamma"), &b,
                 SHADER_UNIFORM_INT);
  SetShaderValue(skybox.materials[0].shader,
                 GetShaderLocation(skybox.materials[0].shader, "vflipped"), &c,
                 SHADER_UNIFORM_INT);

  // Load cubemap shader and setup required shader locations
  Shader shdrCubemap =
      LoadShader("../../Minero-Game/resources/cubemap.vs", "../../Minero-Game/resources/cubemap.fs");

  const static int equimap = 0;
  SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), &equimap, SHADER_UNIFORM_INT);

  char skyboxFileName[256] = {0};

  Texture2D panorama; // Skybox texture.
  if (useHDR)
  {
    TextCopy(skyboxFileName, "../../Minero-Game/resources/daytime.hdr");

    // Load HDR panorama (sphere) texture
    panorama = LoadTexture(skyboxFileName);


    game->renderer->env->Panorama = panorama;
    
    // Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR
    // texture NOTE 1: New texture is generated rendering to texture, shader
    // calculates the sphere->cube coordinates mapping NOTE 2: It seems on some
    // Android devices WebGL, fbo does not properly support a FLOAT-based
    // attachment, despite texture can be successfully created.. so using
    // PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of
    // PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = Global::MeshTools::GenTextureCubemap(
        shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    // /);

    // UnloadTexture(panorama); // Texture not required anymore, cubemap
    //  already generated
  }
  else
  {
    // Load non HDR panorama (cube) texture
    Image img = LoadImage("../../Minero-Game/resources/skybox.png");
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
        img, CUBEMAP_LAYOUT_AUTO_DETECT); // CUBEMAP_LAYOUT_PANORAMA
    UnloadImage(img);
  }

  player->model.materials[0].shader = postProcessShader;
  postProcessShader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(postProcessShader, "matModel");

  Light Sun[2] = {0};

  // Sun creation
  Sun[0] = CreateLight(LIGHT_DIRECTIONAL, Vector3{50.0f, 50.0f, 50.0f},
                       Vector3Zero(), WHITE, postProcessShader);
  Sun[1] = CreateLight(LIGHT_POINT, Vector3{50.0f, 50.0f, 50.0f}, Vector3Zero(),
                       BLACK, postProcessShader); // Ambient color.

    

  // Assignment of shaders

  //--------------------------------------------------------------------------------------
  Image PerlinTest = GenImagePerlinNoise(1000, 1000, 0, 0, 10.0f);

  ExportImage(PerlinTest, "PerlinTest.png");

  Mesh mesh = GenMeshHeightmap(
      PerlinTest, Vector3{16, 8, 16});   // Generate heightmap mesh (RAM and VRAM)
  Model model = LoadModelFromMesh(mesh); // Load model from generated mesh

  UnloadImage(PerlinTest); // Unload heightmap PerlinTest from RAM, already uploaded to VRAM

  Color skyColor = SKYBLUE;
  Color groundColor = GRAY;
  // ambient light level
  int amb = GetShaderLocation(postProcessShader, "ambient");
  static float shaderamb[4] = {0.02f, 0.02f, 0.02f, 0.02f};

  SetShaderValue(postProcessShader, amb, &shaderamb, UNIFORM_VEC4);

  // commented since this needs to be cleaned up.
  // Flashlight *flashlight = new Flashlight(player->cameraComponent->getSelfCamera(), postProcessShader);

  Vector3 lightDirection[3] = {
      Sun[0].target,
      Sun[1].target,
      // flashlight->GetLight().target

  }; // Example light direction pointing upwards
  SetShaderValue(postProcessShader, Sun[0].targetLoc, &lightDirection[0],
                 SHADER_UNIFORM_VEC3);
  SetShaderValue(postProcessShader, Sun[1].targetLoc, &lightDirection[1],
                 SHADER_UNIFORM_VEC3);
  // SetShaderValue(postProcessShader, flashlight->GetLight().targetLoc, &lightDirection[2], SHADER_UNIFORM_VEC3);

  SetShaderValue(postProcessShader, GetShaderLocation(postProcessShader, "skyColor"), &skyColor, SHADER_UNIFORM_VEC4);
  SetShaderValue(postProcessShader, GetShaderLocation(postProcessShader, "groundColor"), &groundColor, SHADER_UNIFORM_VEC4);

  SetShaderValue(postProcessShader, GetShaderLocation(postProcessShader, "ambientColor"), &amb, SHADER_UNIFORM_VEC4);

  bool CreateSunRay = true;

  Vector3 Orgin =
      Vector3{player->cameraComponent->getPosition().x, player->cameraComponent->getPosition().y - 10.0f,
              player->cameraComponent->getPosition().z};
  Logman::CustomLog(LOG_DEBUG, "Trace ", NULL);
  Vector3 testblock = Vector3One();

  Logman::CustomLog(LOG_DEBUG, "Generating World...", NULL);

  double Starttime = GetTime();

  // terrain generation should go here

  double current = GetTime();

  Logman::CustomLog(LOG_DEBUG, TextFormat("World generated in %d", Starttime - current),
                    NULL);

  // Image Perlin = GenImagePerlinNoise(100, 100, 0, 0, 1.0f);
  // ExportImage(Perlin, "perlin.png");
  // GenMeshHeightmap(Perlin, (Vector3){100.0f, 10.0f, 100.0f})
  Model terrain = LoadModelFromMesh(GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

  terrain.materials[0].shader = LoadShader("../../Minero-Game/resources/terrain.vert", "../../Minero-Game/resources/terrain.frag");

  // UnloadImage(Perlin);
  // UnloadImage(PerlinTest);

  // test if temp folder exists
  if (!DirectoryExists("temp"))
  {
    system("mkdir temp");
  }

  Texture tex; // TODO : Find out what this is.

  // const static int res[2] = {game->windowHeight, game->windowWidth};
  // SetShaderValue(postProcessShader, GetShaderLocation(postProcessShader, "resolution"), &res, SHADER_UNIFORM_VEC2);
 
 game->renderer->env->shdrCubemap = shdrCubemap;
 
  
  ConsoleGUI *console = new ConsoleGUI(true);



// Checks if the music should be played, and plays it if it should be.
 if (game->enableMusic)
 {
   PlayMusicStream(LoadMusicStream("../../Minero-Game/resources/Audio/OST/Minero.mp3"));
 }

  // Main menu, Not complete!
  if (SkipMainMenu != true)
  {
    // Declare main loading done
    Logman::CustomLog(LOG_INFO, "Main loading done, Main menu drawing", NULL);

    // Main menu Loop
    while (currentScreen == Main && !WindowShouldClose())
    {

      BeginDrawing();

      ClearBackground(WHITE);

      mmen_start->draw(); // draws the start button
      EndDrawing();

      // key to go to the game incase button kaput
      if (IsKeyPressed(KEY_DELETE))
      {
        currentScreen = Gameplay;
      }

      // Main Menu Start Button
      if (mmen_start->IsClicked())
      {
        currentScreen = Gameplay;
      }
    }
  }
  delete mmen_start;
  //player->Setup();
//GameObject::PushObject(new Plane(postProcessShader, Vector3{0.0f, 0.0f, 0.0f}));
  // Game Loop

  Logman::Log("hello from cmake");
  while (!WindowShouldClose())
  {
    //Global::Time::Update();

    // TODO : Move input crap into another thread.
    // Pause Menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
      // Todo, move the menuCamera to be created on game startup and then hidden. it gets shown on if statement validation
      bool exit = false;
      bool manualExit = false;

      MenuCamera *men_pause = new MenuCamera();
      ButtonR *save = new ButtonR("Save", 100, 100);
      ButtonR *Options = new ButtonR("Options", 100, 200);
      ButtonR *exitButton = new ButtonR("Exit to Windows", 100, 300);


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
        /*
        if (save->IsClicked())
        {

          // todo : implement Saving game data, probably use the Objects vector.
          const char *filename = "save.sav";

          std::vector<void *> data;

          for (int i = 0; i < GameObject::GameObjects.size(); i++)
          {
            data.push_back(GameObject::GameObjects[i]);
          }
          SaveFileData(filename, &data, sizeof(data));

          Logman::CustomLog(LOG_DEBUG, LoadFileText(filename), NULL);
        }*/

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
      //UnloadTexture(tex);
      delete men_pause;
      delete save;
      delete exitButton;
      if (manualExit)
      {

        Logman::CustomLog(LOG_INFO, "Exiting Game", NULL);
        break;
      }
    }


    if (IsKeyPressed(KEY_U)) {

    }
    // update ray
    ray.position = player->cameraComponent->getPosition();
    ray.direction = player->cameraComponent->getTarget();

    // Show Debug shit
    if (IsKeyDown(KEY_END))
    {
      BeginDrawing();
      BeginMode3D(player->cameraComponent->getSelfCamera());
      // Sun Rays
      DrawLine3D(Sun[0].position, player->cameraComponent->getPosition(), RED);
      EndMode3D();
      EndDrawing();
    }

    // Check for left click

    if (IsKeyPressed(KEY_F))
    {
      // flashlight->Switch();
    }

    // If statement for block placing.
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
      Vector3 placepos = player->cameraComponent->getTarget();

      GameObject::PushObject(new Block(BlockStone, Vector3{roundf(placepos.x), roundf(placepos.y), roundf(placepos.z)}, WHITE, postProcessShader, DefaultBlockModel));
    }

    if (!IsKeyDown(KEY_LEFT_ALT))
    {
      if (!IsCursorHidden())
      {
        DisableCursor();
      }
      UpdateCamera(player->cameraComponent->getSelfCameraPointer(), player->cameraMode); // Update camera
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

    if (IsKeyDown(KEY_SPACE))
    {

      // player->cameraComponent->setPosition(Vector3{player->cameraComponent->getPosition().x, player->cameraComponent->getPosition().y + 1.0f, player->cameraComponent->getPosition().z});

      CameraMoveUp(player->cameraComponent->getSelfCameraPointer(), 0.1f);
    }

    if (IsKeyDown(KEY_C))
    {

      // player->cameraComponent->setPosition(Vector3{player->cameraComponent->getPosition().x, player->cameraComponent->getPosition().y - 0.1f, player->cameraComponent->getPosition().z});
      CameraMoveUp(player->cameraComponent->getSelfCameraPointer(), -0.1f);
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      player->isRunning = true;
      
    } else {
      player->isRunning = false;
    }

    if (IsKeyDown(KEY_Y)) {
      player->healthComp->DamagePlayer(0.1f);
    }
    // TODO : day night affect

    // float h = Vector3Distance(player->getPosition(), Sun[0].position);
    //   SetShaderValue(postProcessShader, GetShaderLocation(postProcessShader, "distance"), &h, SHADER_UNIFORM_FLOAT);
    //----------------------------------------------------------------------------------

    PollInputEvents(); // helps for some reason?

    // Update the light shader with the camera view position
    // Update the shader with the camera view vector (points towards { 0.0f,
    // 0.0f, 0.0f })

    float cameraPos[3] = {player->cameraComponent->getPosition().x,
                          player->cameraComponent->getPosition().y,
                          player->cameraComponent->getPosition().z};

    Vector3 SunPos = {Sun[0].position.x, Sun[0].position.y, Sun[0].position.z};

    UpdateLightValues(postProcessShader, Sun[0]);
    UpdateLightValues(postProcessShader, Sun[1]);

    // flashlight->Update(postProcessShader, player->cameraComponent->getPosition(), player->cameraComponent->getPosition());

    SetShaderValue(postProcessShader, postProcessShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

    game->renderer->StartTexturing();


    
    BeginMode3D(player->cameraComponent->getSelfCamera());

    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    DrawModel(skybox, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();

    // rlPopMatrix()

    // DrawModel(terrain, Vector3SubtractValue(Vector3Zero(), 2.0f), 1.0f, GREEN); // not needed atm, if it isnt for a while, it will get deleted

    //  We are inside the cube, we need to disable backface culling!

    BeginShaderMode(shdrCubemap);
    GameObject::Render();
    EndShaderMode();
    BeginShaderMode(postProcessShader);
    GameObject::Render();
    EndShaderMode();

    
    // EndShaderMode();
    game->renderer->End3D();

    game->renderer->StopTexturing();
    rlPopMatrix();


    // depth mask
    game->renderer->StartDepthMode();

    BeginMode3D(player->cameraComponent->getSelfCamera());

    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    DrawModel(skybox, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();


    BeginShaderMode(shdrCubemap);
    GameObject::Render();
    EndShaderMode();
    BeginShaderMode(postProcessShader);
    GameObject::Render();
    EndShaderMode();

    // EndShaderMode();
    game->renderer->End3D();

    game->renderer->StopTexturing();
    rlPopMatrix();

    SetTextureFilter(game->renderer->fbo.texture, TEXTURE_FILTER_BILINEAR);
    
    game->renderer->StartDraw();
      
    // BeginShaderMode(shdrCubemap);
    // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
    DrawTextureRec(game->renderer->fbo.texture, Rectangle{ 0, 0, (float)(game->renderer->fbo.texture.width), (float)(-game->renderer->fbo.texture.height) }, Vector2{ 0, 0 }, WHITE);
                ClearBackground(RAYWHITE);

    //BeginMode2D(menucamera->camera);

    // Crosshair
    player->healthComp->healthBar->Draw({0.0f, (float)screenWidth + 500});
    
    DrawCircle(game->windowWidth/2, game->windowHeight/2, 3, GRAY);
    //EndMode2D();

    game->renderer->EndDraw();


  }


  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  // UnloadRenderTexture(fbo);
  CloseAudioDevice();

  //--------------------------------------------------------------------------------------

  // Unload Models/Textures
  // UnloadTexture(texture); // Unload texture


  UnloadModel(model); // Unload model
  UnloadModel(DefaultBlockModel);

  UnloadShader(postProcessShader);

  UnloadImage(PerlinTest);
  UnloadImage(PerlinTest);

  using namespace std;
  {
    remove("PerlinTest.png");
    remove("HMap.png");
  }

  game->EndGame();
  delete game;
  delete mmen_start; // Deletes the main menu
  delete menucamera;
  delete block;
  delete player;
  GameObject::FlushBuffer();
  delete console;
  // delete heightmap;

  // delete flashlight;

  return 0;
}

/*
                                            Code Graveyard
_________________________________________________________________________________________________________________________

Wow such empty





*/