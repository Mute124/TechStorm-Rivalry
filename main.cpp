// Run Args
bool SkipMainMenu = true;

#include "lib/Buttons/src/ButtonR.h" // Needed for buttons.
// Raylib Framework
#include "common.h"

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

#include "Engine/Classes/Env/Light/Light.h"
// #define RLIGHTS_IMPLEMENTATION
// #include "lib/rlights.h"

#define RAYGUI_IMPLEMENTATION
#include "../raygui.h"

#define GUI_OPTIONS_IMPLEMENTATION
#include "Minero/gui_Options.h"

#include "Styles/bluish/style_bluish.h"
// This translates the current screen
typedef enum
{
  Main = 0,
  PauseMenu,
  Gameplay

} GameScreen;


RenderTexture2D LoadShadowmapRenderTexture(int width, int height);
void UnloadShadowmapRenderTexture(RenderTexture2D target);
// This is a struct that is a utility for the terrain generator. Dont touch. It
// is mainly used within the GenX, Y, and Z funcs

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
  game->renderer->pbrShader = LoadShader(TextFormat("../../Minero-Game/resources/shaders/glsl%i/pbr.vs", GLSL_VERSION),
                                         TextFormat("../../Minero-Game/resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));
  game->renderer->pbrShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(game->renderer->pbrShader, "albedoMap");
  // WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture
  // They are passed as to the SHADER_LOC_MAP_METALNESS location for convenience,
  // shader already takes care of it accordingly
  game->renderer->pbrShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(game->renderer->pbrShader, "mraMap");
  game->renderer->pbrShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(game->renderer->pbrShader, "normalMap");
  // WARNING: Similar to the MRA map, the emissive map packs different information
  // into a single texture: it stores height and emission data
  // It is binded to SHADER_LOC_MAP_EMISSION location an properly processed on shader
  game->renderer->pbrShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(game->renderer->pbrShader, "emissiveMap");
  game->renderer->pbrShader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(game->renderer->pbrShader, "albedoColor");
  // optimization

  // Setup additional required shader locations, including lights data
  game->renderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(game->renderer->pbrShader, "viewPos");
  int lightCountLoc = GetShaderLocation(game->renderer->pbrShader, "numOfLights");
  int maxLightCount = MAX_LIGHTS;
  SetShaderValue(game->renderer->pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

  // Setup ambient color and intensity parameters
  float ambientIntensity = 0.02f;
  Color ambientColor = Color{26, 32, 135, 255};
  Vector3 ambientColorNormalized = Vector3{ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f};
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

  // Get location for shader parameters that can be modified in real time
  int emissiveIntensityLoc = GetShaderLocation(game->renderer->pbrShader, "emissivePower");
  int emissiveColorLoc = GetShaderLocation(game->renderer->pbrShader, "emissiveColor");
  int textureTilingLoc = GetShaderLocation(game->renderer->pbrShader, "tiling");

  Model DefaultBlockModel = LoadModelFromMesh(
      GenMeshCube(BLOCK_SIZE, BLOCK_SIZE,
                  BLOCK_SIZE)); // this is the default model used in blocksd.

  const int Playersize = 3;
  Model PlayerModel = LoadModelFromMesh(GenMeshCube(3.0f, 3.0f, 3.0f)); // Generates the playermodel. For right now it is a cube.
  Player *player = new Player(Vector3{0.0f, 2.0f, 4.0f}, 100, PlayerModel, CAMERA_FIRST_PERSON);

  GameObject::PushObject(player);

  // Block Initialization

  Block *block = new Block(BlockDirt, Vector3Zero(), WHITE, game->renderer->pbrShader, LoadModel("resources/old_car_new.glb"));

  GameObject::PushObject(block);

  // Load skybox model
  // skybox creation.
  Mesh skyboxMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
  Model skybox = LoadModelFromMesh(skyboxMesh);

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
    TextCopy(skyboxFileName, "../../Minero-Game/resources/milkyWay.hdr");

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
    //   already generated
  }
  else
  {
    // Load non HDR panorama (cube) texture
    Image img = LoadImage("../../Minero-Game/resources/textures/space.png");
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
        img, CUBEMAP_LAYOUT_AUTO_DETECT); // CUBEMAP_LAYOUT_PANORAMA
    UnloadImage(img);
  }

  Light sun = CreateLight(LIGHT_POINT, Vector3{1.0f, 10.0f, 1.0f}, Vector3One(),
                          BLUE, 4.0f, game->renderer->pbrShader); // Ambient color.;
                                                                  // Assignment of shaders
  // NOTE: By default, the texture maps are always used
  int usage = 1;
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
  SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);

  //--------------------------------------------------------------------------------------

  Vector3 Orgin =
      Vector3{player->cameraComponent->getPosition().x, player->cameraComponent->getPosition().y - 10.0f,
              player->cameraComponent->getPosition().z};

  Model terrain = LoadModelFromMesh(GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));

  terrain.materials[0].shader = LoadShader("../../Minero-Game/resources/terrain.vert", "../../Minero-Game/resources/terrain.frag");

  // test if temp folder exists
  if (!DirectoryExists("temp"))
  {
    system("mkdir temp");
  }

  game->renderer->env->shdrCubemap = shdrCubemap;

  ConsoleGUI *console = new ConsoleGUI(true);

  GuiOptionsState optionsState = InitGuiOptions();

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

  while (!WindowShouldClose())
  {
    // Global::Time::Update();

    // TODO : Move input crap into another thread.
    // Pause Menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
      /*

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
      // UnloadTexture(tex);
      delete men_pause;
      delete save;
      delete exitButton;
      if (manualExit)
      {

        Logman::CustomLog(LOG_INFO, "Exiting Game", NULL);
        break;
      }


      */

    }
    // update ray
    ray.position = player->cameraComponent->getPosition();
    ray.direction = player->cameraComponent->getTarget();

    // If statement for block placing.
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
      Vector3 placepos = player->cameraComponent->getTarget();

      GameObject::PushObject(new Block(BlockStone, Vector3{roundf(placepos.x), roundf(placepos.y), roundf(placepos.z)}, WHITE, game->renderer->pbrShader, DefaultBlockModel));
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

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
      player->isRunning = true;
    }
    else
    {
      player->isRunning = false;
    }

    if (IsKeyDown(KEY_Y))
    {
      player->healthComp->DamagePlayer(0.1f);
    }

    // TODO : day night affect

    PollInputEvents(); // helps for some reason?
    float cameraPos[3] = {player->cameraComponent->getPosition().x,
                          player->cameraComponent->getPosition().y,
                          player->cameraComponent->getPosition().z};

    sun.position = player->cameraComponent->getTarget();
    UpdateLight(game->renderer->pbrShader, sun);
    UpdateLight(game->renderer->bloomShader, sun);
    SetShaderValue(game->renderer->pbrShader, game->renderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW], &cameraPos, SHADER_UNIFORM_VEC3);

    game->renderer->StartTexturing();

    BeginMode3D(player->cameraComponent->getSelfCamera());

    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    // DrawModel(skybox, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();

    // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
    SetShaderValue(game->renderer->pbrShader, textureTilingLoc, &block->carTextureTiling, SHADER_UNIFORM_VEC2);
    Vector4 carEmissiveColor = ColorNormalize(block->model.materials[0].maps[MATERIAL_MAP_EMISSION].color);
    SetShaderValue(game->renderer->pbrShader, emissiveColorLoc, &carEmissiveColor, SHADER_UNIFORM_VEC4);
    float emissiveIntensity = 0.01f;
    SetShaderValue(game->renderer->pbrShader, emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);

    GameObject::RenderObjects();

    // EndShaderMode();
    game->renderer->End3D();

    game->renderer->StopTexturing();
    rlPopMatrix();

    SetTextureFilter(game->renderer->fbo.texture, TEXTURE_FILTER_ANISOTROPIC_16X);

    game->renderer->StartDraw();

    BeginShaderMode(game->renderer->bloomShader);
    // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
    DrawTextureRec(game->renderer->fbo.texture, Rectangle{0, 0, (float)(game->renderer->fbo.texture.width), (float)(-game->renderer->fbo.texture.height)}, Vector2{0, 0}, WHITE);

    EndShaderMode();
    ClearBackground(RAYWHITE);
    DrawFPS(100, 100);
    player->healthComp->healthBar->Draw({0.0f, (float)screenWidth + 500});

    // Crosshair
    DrawCircle(game->windowWidth / 2, game->windowHeight / 2, 3, GRAY);

    // EndMode2D();

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

  UnloadModel(DefaultBlockModel);

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
  return 0;
}

RenderTexture2D LoadShadowmapRenderTexture(int width, int height)
{
  RenderTexture2D target = {0};

  target.id = rlLoadFramebuffer(width, height); // Load an empty framebuffer
  target.texture.width = width;
  target.texture.height = height;

  if (target.id > 0)
  {
    rlEnableFramebuffer(target.id);

    // Create depth texture
    // We don't need a color texture for the shadowmap
    target.depth.id = rlLoadTextureDepth(width, height, false);
    target.depth.width = width;
    target.depth.height = height;
    target.depth.format = 19; // DEPTH_COMPONENT_24BIT?
    target.depth.mipmaps = 1;

    // Attach depth texture to FBO
    rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

    // Check if fbo is complete with attachments (valid)
    if (rlFramebufferComplete(target.id))
      TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

    rlDisableFramebuffer();
  }
  else
    TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

  return target;
}

// Unload shadowmap render texture from GPU memory (VRAM)
void UnloadShadowmapRenderTexture(RenderTexture2D target)
{
  if (target.id > 0)
  {
    // NOTE: Depth texture/renderbuffer is automatically
    // queried and deleted before deleting framebuffer
    rlUnloadFramebuffer(target.id);
  }
}

