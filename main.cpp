// Run Args
bool SkipMainMenu = true;


/*
---------------------------------------------------------------------------------
| 					         Includes											|
---------------------------------------------------------------------------------
*/
#include "Button.h" // TODO : Can this be moved to common.h?
#include "common.h"

// Game Engine Includes
#include "Game.h"
#include "Globals.h"
#include "Block.h"
#include "Gameobject.h"
#include "MenuCamera.h"
#include "Player.h"
#include "Logman.h"
#include "ConfigMan.h" 
#include "Light.h"
#include "Layer.h"
#include "InventoryManager.h"

// std library includes. TODO : Is this still needed?
#include <time.h>
#include <vector> // needed for game object list

// the enumeration of what screen is being run. See Documentation for more info.
typedef enum
{
	Main = 0,
	PauseMenu,
	Gameplay
} GameScreen;


// TODO : Finish shadowmapping
RenderTexture2D LoadShadowmapRenderTexture(int width, int height);
void UnloadShadowmapRenderTexture(RenderTexture2D target);


/*
---------------------------------------------------------------------------------
| 					        Variable Setup										|
---------------------------------------------------------------------------------
*/

// Main.cpp global variables get declared here! (if they need to be used by the main function and other functions, they belong here)

// Booleans

// Lets the program know if the game should use HDR as the skybox
bool useHDR = true;

// Initialie the condition for the breathing sound.
bool isBreathing = false;



// Viewsway
float swayAmount = 0.0003f;
float swaySpeed = 0.02f;
float swayTimer = 0.0f;


// Near death affect.
// Important : THESE ARE REQUIRED FOR THE ARCH ALGORITHM TO WORK!
float nearDeathTimer = 0.0f; // The X axis
float amplitude = 255; // How high the Parabola goes
float frequency = 5; // How often the arches are
float steepness = 2.4f; // How steep the curve is, NOTE : If it is an odd number, it will not show as it only works for even times.
float offset = 1; // Offset of the arches from x = 0
const float scaleFactor = 25; // Scaling factor, how much the parabolas is scaled
float nearDeathIntensity = 0.0f; // The Y Axis of the algorithm

// Health bar fuckery
float healthBarPositionX = 0.0f;
float healthBarPositionY = 0.0f;
int healthBarOffsetX = 0;
int healthBarOffsetY = 500;

// represents the raycasting from the player to the world. 
Ray ray;


int main(void)
{
	//TODO: Is this still relevant?
	GameScreen currentScreen = Main;

	// -----------------------------------------------------------------------------
	// Game Setup
	// -----------------------------------------------------------------------------

	// Create game & load it into memory.
	Game* game = new Game();

	// Start the game and do any needed setup
	game->StartGame();

	// IMPORTANT : Do not remove this or delete it as it is the manager of all game objects!
	GameobjectManager* gameObjectManager = new GameobjectManager();

	// test if temp folder exists, if not create it
	if (!DirectoryExists("temp"))
	{
		system("mkdir temp"); // run the system command to create the folder. Note : This is a windows command.
	}


	// -----------------------------------------------------------------------------
	// Load Game Assets
	// -----------------------------------------------------------------------------

	// Ambiance
	// The passive sound of your breathing.
	//ToDo: tweak to sound more natural. This could be based on fatigue, stress, or something.
	Sound breathingSound = LoadSound("resources/audio/breathing.mp3");

	// Items
	// Create a new inventory manager instance
	InventoryMan* inventoryMan = new InventoryMan("data/Items/resources.tsr");

	// set up all the items concurrently.
	std::thread itemsSetupThread(inventoryMan->SetupItems);

	// Tell the thread to join with the main thread. (Merges the two)
	itemsSetupThread.join();

	// Note : This is temporary and is solely to test the inventory system loading items
	Logman::Log(TextFormat("%i", inventoryMan->itemCount));


	/*
	---------------------------------------------------------------------------------
	| 					        Shader Setup										|
	---------------------------------------------------------------------------------
	*/

	// -----------------------------------------------------------------------------
	// Set up the PBR shader
	// -----------------------------------------------------------------------------
	
	// Load the shader into memory
	game->renderer->pbrShader = LoadShader(TextFormat("resources/shaders/glsl%i/pbr.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));

	// Get shader locations
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

	// Setup additional required shader locations, including lights data
	game->renderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(game->renderer->pbrShader, "viewPos");
	int lightCountLoc = GetShaderLocation(game->renderer->pbrShader, "numOfLights"); 
	
	// set it to the value of the MAX_LIGHTS macro and pass it to the shader
	int maxLightCount = MAX_LIGHTS; 
	SetShaderValue(game->renderer->pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

	// Setup ambient color and intensity (brightness) parameters
	float ambientIntensity = 0.02f;
	Color ambientColor = Color{ 26, 32, 135, 255 };
	Vector3 ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

	// Get location for shader parameters that can be modified
	int emissiveIntensityLoc = GetShaderLocation(game->renderer->pbrShader, "emissivePower");
	int emissiveColorLoc = GetShaderLocation(game->renderer->pbrShader, "emissiveColor");
	int textureTilingLoc = GetShaderLocation(game->renderer->pbrShader, "tiling");

	/*
	---------------------------------------------------------------------------------
	| 					        Object Creation										|
	---------------------------------------------------------------------------------
	*/

	// -----------------------------------------------------------------------------	
	// Block Initialization
	// -----------------------------------------------------------------------------	
	
	// Create a default block model with a length, width, and height of the value of BLOCK_SIZE. This creates a cube mesh with a length, width, and height of BLOCK_SIZE and then converts it to a model, loading it 
	// into memory.
	Model DefaultBlockModel = LoadModelFromMesh(
		GenMeshCube(BLOCK_SIZE, BLOCK_SIZE,
			BLOCK_SIZE)); // this is the default model used in blocksd.


	// todo : change all use instances of DefaultBlockModel to use the global default model.
	SetDefaultModel(DefaultBlockModel);

	// Construct the block object
	Block* block = new Block(Vector3Zero(), BLACK, game->renderer->pbrShader, DefaultBlockModel);

	// Finally push it off to the object manager
	gameObjectManager->Push(block);

	// -----------------------------------------------------------------------------
	// Player Initialization
	// -----------------------------------------------------------------------------
	
	// TODO : Is the Playersize variable needed and or relevant?
	
	// Create the player model
	// NOTE: This model is TEMPORARY! It will be deleted after a proper model is made.
	// Refers to the size of the player model. Same process as the default block model creation.
	const int Playersize = 3;
	Model PlayerModel = LoadModelFromMesh(GenMeshCube(Playersize, Playersize, Playersize)); 
	
	// Construct the player object
	Player* player = new Player(Vector3{ 0.0f, 2.0f, 4.0f }, 100, PlayerModel, CAMERA_FIRST_PERSON);

	// Finally push it off to the object manager
	gameObjectManager->Push(player);

	// -----------------------------------------------------------------------------
	// skybox creation.
	// -----------------------------------------------------------------------------
	

	// Skybox geometry generation step
	Mesh skyboxMesh = GenMeshCube(1.0f, 1.0f, 1.0f);

	// Skybox model loading step
	Model skybox = LoadModelFromMesh(skyboxMesh);

	// Load skybox shader and set required locations step
	// NOTE: Some locations are automatically set at shader loading
	skybox.materials[0].shader = LoadShader("resources/skybox.vs", "resources/skybox.fs");

	// since the compiler complains about the references of such, these three vars
	// are for the skybox shaders. They will be deleted after.
	static int skyboxEnvironmentMap = MATERIAL_MAP_CUBEMAP;

	// Both variables are equal to 1 if useHDR is true, otherwise 0
	static int skyboxUsesGamma = { useHDR ? 1 : 0 };
	static int skyboxIsVFlipped = { useHDR ? 1 : 0 };

	// Load the environment map
	SetShaderValue(
		skybox.materials[0].shader,
		GetShaderLocation(skybox.materials[0].shader, "environmentMap"), &skyboxEnvironmentMap,
		SHADER_UNIFORM_INT);

	// Should the shader use gamma correction
	SetShaderValue(skybox.materials[0].shader,
		GetShaderLocation(skybox.materials[0].shader, "doGamma"), &skyboxUsesGamma,
		SHADER_UNIFORM_INT);

	// Is the skybox flipped vertically
	SetShaderValue(skybox.materials[0].shader,
		GetShaderLocation(skybox.materials[0].shader, "vflipped"), &skyboxIsVFlipped,
		SHADER_UNIFORM_INT);

	// -----------------------------------------------------------------------------
	// Cubemap Loading
	// -----------------------------------------------------------------------------
	// This step is part of the skybox creation.

	// Load cubemap shader and setup required shader locations
	Shader shdrCubemap =
		LoadShader("resources/cubemap.vs", "resources/cubemap.fs");

	// set shdrCubemap's equirectangular map.
	const static int equimap = 0;
	SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), &equimap, SHADER_UNIFORM_INT);


	// Note: The filename is hardcoded here and also has a limit of 256 characters!
	// I will be dissapointed if you somehow dont know what that variable does...
	char skyboxFileName[256] = { 0 };

	// This is the panoramic texture, It is used IF useHDR is true
	Texture2D panorama = { 0 };

	if (useHDR)
	{
		TextCopy(skyboxFileName, "resources/milkyWay.hdr");

		// Load HDR panorama (sphere) texture
		panorama = LoadTexture(skyboxFileName);

		// Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR
		// texture NOTE 1: New texture is generated rendering to texture, shader
		// calculates the sphere->cube coordinates mapping NOTE 2: It seems on some
		// Android devices WebGL, fbo does not properly support a FLOAT-based
		// attachment, despite texture can be successfully created.. so using
		// PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of
		// PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
		skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(
			shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	}
	else
	{
		// it isnt going to be used. so it can fuck off.
		UnloadTexture(panorama);

		// Load non HDR panorama (cube) texture
		Image img = LoadImage("resources/textures/space.png");

		// Set it's cubemap texture.
		skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(
			img, CUBEMAP_LAYOUT_AUTO_DETECT); // CUBEMAP_LAYOUT_PANORAMA

		// unload img as we dont need it anymore.
		UnloadImage(img);
	}


	// -----------------------------------------------------------------------------
	// Light Setup
	// -----------------------------------------------------------------------------

	
	// Create the Sunlight
	// Note : this is not it's final form, it is just a placeholder for testing
	// ToDo: finalize this step and functionality
	Light sun = CreateLight(LIGHT_POINT, Vector3{ 1.0f, 0.0f, 1.0f }, Vector3One(),
		BLUE, 4.0f, game->renderer->pbrShader); // Ambient color.;

	// Enable the sun as a precautionary measure.
	sun.enabled = true;


	// -----------------------------------------------------------------------------
	// PBR Finalizations
	// -----------------------------------------------------------------------------

	// we need to finalize the PBR shader and give the shader any last minute data.
	
	// Assignment of shaders
	// NOTE: By default, the texture maps are always used
	int usage = 1;
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);

	//--------------------------------------------------------------------------------------


	// TODO : Is this still relevant and figure out what the hell this does.
	Vector3 Orgin = Vector3
	{ 
		player->cameraComponent->GetPosition().x, 
		player->cameraComponent->GetPosition().y - 10.0f,
		player->cameraComponent->GetPosition().z 	
	};


	// Note: See the comment regarding main menu
	//delete mmen_start;

	// The texture for the near death affect initialization
	Texture2D nearDeathTex = { 0 };

	// The image for the near death affect initialization
	Image nearDeathAffect = { 0 };

	// The color for the near death affect initialization
	Color nearDeathColor = { 0 };

	/*
	---------------------------------------------------------------------------------
	| 					         HealthBar Setup									|
	---------------------------------------------------------------------------------
	*/

	healthBarPositionX = game->windowWidth + healthBarOffsetX;
	healthBarPositionY = game->windowHeight + healthBarOffsetY;


	// Now we can run the game loop and start playing!
	while (!WindowShouldClose())
	{
		// NOTE : This is a very basic implementation of placing an object into the world. This is temporary and should be fleshed out.
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{

			Vector3 placepos = player->cameraComponent->GetTarget();

			gameObjectManager->Push(new Block(Vector3{ roundf(placepos.x), roundf(placepos.y), roundf(placepos.z) }, WHITE, game->renderer->pbrShader, GetDefaultModel()));
		}

		// Allow the cursor to be seen even if it is within the game. (It unlocks the cursor)
		if (!IsKeyDown(KEY_LEFT_ALT))
		{
			if (!IsCursorHidden())
			{
				DisableCursor();
			}
			UpdateCamera(player->cameraComponent->GetSelfCameraPointer(), player->cameraMode); // Update camera
		}
		else
		{
			EnableCursor();
		}

		// Take a screenshot
		if (IsKeyPressed(KEY_F9))
		{
			// take a screenshot
			for (int i = 0; i < INT_MAX; i++)
			{
				const char* fileName = TextFormat("screen%i.png", i);
				// if there isnt a duplicate file, it then will create a screenshot.
				if (FileExists(fileName) == 0)
				{
					TakeScreenshot(fileName);
					break;
				}
			}
		}

		// Sprinting Mechanic
		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			player->isRunning = true;
		}
		else
		{
			player->isRunning = false;
		}

		// NOTE : This is temporary and is only to test the health system
		if (IsKeyDown(KEY_Y))
		{
			player->healthComp->DamagePlayer(5.0f);
		}
		/*
		---------------------------------------------------------------------------------
		| 					         If Statements go here!								|
		---------------------------------------------------------------------------------
		*/
		// TODO : Move input crap into another thread.
		// Pause Menu
		if (IsKeyPressed(KEY_ESCAPE))
		{
			// Todo, move the menuCamera to be created on game startup and then hidden. it gets shown on if statement validation
			bool exit = false;
			bool manualExit = false;

			MenuCamera* men_pause = new MenuCamera();
			ButtonR* save = new ButtonR("Save", 100, 100);
			ButtonR* Options = new ButtonR("Options", 100, 200);
			ButtonR* exitButton = new ButtonR("Exit to Windows", 100, 300);

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
					const char* filename = "save.sav";

					std::vector<void*> data;

					for (int i = 0; i < gameObjectManager->objectsVector.size(); i++)
					{
						data.push_back(gameObjectManager->objectsVector[i]);
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
		}

		if (IsKeyPressed(KEY_E)) {
			// todo : Code the inventory menu AAAAAAAA
		}

		// breathing ambiance code

		// If the sound is not playing, play it
		if (!isBreathing) {
			isBreathing = true;

			PlaySound(breathingSound);
		}
		else {
			// set isBreathing to the result of IsSoundPlaying(breathingSound)
			isBreathing = IsSoundPlaying(breathingSound);
		}


		// The player's looking direction is the target of the camera. This is the direction the player is looking
		// TODO : Check relevancy.
		ray.position = player->cameraComponent->GetPosition();
		ray.direction = player->cameraComponent->GetTarget();





		// Sway timer is equal to swayTimer + frame delta time
		swayTimer += GetFrameTime();

		// sway the camera according to the sway algorithm.
		player->cameraComponent->SetTarget(Vector3{ player->cameraComponent->GetTarget().x + sin(swayTimer * swaySpeed) * swayAmount, player->cameraComponent->GetTarget().y, player->cameraComponent->GetTarget().z + cos(swayTimer * swaySpeed) * swayAmount });


		if (player->healthComp->GetHealth() <= 15) {

			// equal to nearDeathTimer + frame delta time
			nearDeathTimer += GetFrameTime();

			// Arch algorithm implementation for color
			nearDeathIntensity = ArchAlgorithm(amplitude, frequency, nearDeathTimer, steepness, offset, 255, scaleFactor);

			// what color the screen should pulsate
			nearDeathColor = Color{ (unsigned char)nearDeathIntensity, 0, 0, 100 };

			// convert nearDeathColor to an image
			nearDeathAffect = GenImageColor(game->renderer->fbo.texture.width, game->renderer->fbo.texture.height, nearDeathColor);


			// Set the ambient color to the normalized nearDeathColor
			Vector3 nearDeathAmb = Vector3{ nearDeathColor.r / 255.0f, nearDeathColor.g / 255.0f, nearDeathColor.b / 255.0f };
			// Inform the shader about the new ambient color.
			SetShaderValue(game->renderer->pbrShader, GetShaderLocation(game->renderer->pbrShader, "ambientColor"), &nearDeathAmb, SHADER_UNIFORM_VEC3);

			// Load the image into the texture
			nearDeathTex = LoadTextureFromImage(nearDeathAffect);
			UnloadImage(nearDeathAffect); // We can unload the image now that we have the texture.
		}

		// Stashes input events for later
		PollInputEvents(); // helps for some reason?

		// Where the player's camera is. We need to have this as a float array for the shader
		float cameraPos[3] =
		{
			player->cameraComponent->GetPosition().x,
			player->cameraComponent->GetPosition().y,
			player->cameraComponent->GetPosition().z
		};


		// Update light position
		sun.position = player->cameraComponent->GetPosition();


		// Update the shader with the new light data. Note : any shader that uses lighting will need this data!
		UpdateLight(game->renderer->pbrShader, sun);
		UpdateLight(game->renderer->bloomShader, sun);

		// Send the camera position to the shader
		SetShaderValue(game->renderer->pbrShader, game->renderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW], &cameraPos, SHADER_UNIFORM_VEC3);

		// Update the game object manager
		gameObjectManager->Update();
		game->scriptManager->Update();


		// Start texturing the FBO with what the user will be seeing. This includes UI and Scene objects.
		game->renderer->StartTexturing();

		/*
		---------------------------------------------------------------------------------
		|     2d Ui rendering for BEFORE 3d drawing										|
		---------------------------------------------------------------------------------
		*/


		DrawTextureRec(nearDeathTex, Rectangle{ 0, 0, (float)(game->renderer->fbo.texture.width), (float)(-game->renderer->fbo.texture.height) }, Vector2{ 0, 0 }, WHITE);

		BeginMode3D(player->cameraComponent->GetSelfCamera());

		/*
		---------------------------------------------------------------------------------
		|					Simple Game Objects Drawing									|
		---------------------------------------------------------------------------------
		*/

		/*
			When Skyboxes are fixed, re-add the code snippet below

			rlDisableBackfaceCulling();
			rlDisableDepthMask();
			// DrawModel(skybox, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
			rlEnableBackfaceCulling();
			rlEnableDepthMask();

		*/


		// Set old car model texture tiling, emissive color and emissive intensity parameters on shader
		SetShaderValue(game->renderer->pbrShader, textureTilingLoc, &block->blockTextureTiling, SHADER_UNIFORM_VEC2);

		// Normalize the Emissive map into a 0-1 range. Note : This turns the map into a Vector4, not a color.
		Vector4 carEmissiveColor = ColorNormalize(block->model.materials[0].maps[MATERIAL_MAP_EMISSION].color);
		SetShaderValue(game->renderer->pbrShader, emissiveColorLoc, &carEmissiveColor, SHADER_UNIFORM_VEC4);

		// How bright should the object emit it's emission color.
		float emissiveIntensity = 0.01f;
		SetShaderValue(game->renderer->pbrShader, emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);

		// Render all game objects
		gameObjectManager->RenderObjects();

		// end 3d rendering.
		game->renderer->End3D();

		/*
		---------------------------------------------------------------------------------
		|     2d Ui rendering for AFTER 3d drawing										|
		---------------------------------------------------------------------------------
		*/

		// Stop texturing the FBO with what the user will be seeing.
		game->renderer->StopTexturing();

		// Warning : DO NOT MOVE THIS! this is important! due to a bug within raylib, this must be done after the texturing is done or a stack overflow WILL occur. GOD DAMN IT!
		rlPopMatrix();

		/*
		---------------------------------------------------------------------------------
		| 					Post Process Affects										|
		---------------------------------------------------------------------------------
		*/
		SetTextureFilter(game->renderer->fbo.texture, TEXTURE_FILTER_ANISOTROPIC_16X);

		// Begin drawing mode so we can actually see stuff!
		game->renderer->StartDraw();

		// We must tell OpenGL that we want to use the bloom shader on the FBO!
		BeginShaderMode(game->renderer->bloomShader);

		/*
		---------------------------------------------------------------------------------
		| 					      Bloom Affected										|
		---------------------------------------------------------------------------------
		*/

		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
		DrawTextureRec(game->renderer->fbo.texture, Rectangle{ 0, 0, (float)(game->renderer->fbo.texture.width), (float)(-game->renderer->fbo.texture.height) }, Vector2{ 0, 0 }, WHITE);

		// We need to tell OpenGL that we no longer need the bloom shader to be active.
		EndShaderMode();

		// Draw the FPS onto the screen.
		DrawFPS(100, 100);

		// Draw the player's health bar
		player->healthComp->healthBar->Draw({  healthBarPositionX, healthBarPositionY});

		// Crosshair

		// In order to have it in the middle of the screen, we need to divide the screen dimensions by half. We can then draw a circle in the middle of the screen.
		DrawCircle(game->windowWidth / 2, game->windowHeight / 2, 3, GRAY);

		// Let raylib know that we're done drawing to the screen.
		game->renderer->EndDraw();

		// clear the screen and replace it with black.
		ClearBackground(BLACK);
	}




	/*
	---------------------------------------------------------------------------------
	| 					           Unloading										|
	---------------------------------------------------------------------------------
	*/

	// Unload models.
	// Note : Technically we dont need to unload models as they get automatically unloaded, but it is still good practice. Same goes with textures.
	UnloadModel(DefaultBlockModel);


	// Unload textures
	UnloadTexture(nearDeathTex);

	// Unload images
	UnloadImage(nearDeathAffect);

	// Delete temporary files.
	using namespace std;
	{
		remove("PerlinTest.png");
		remove("HMap.png");
	}

	// End the game, do closing actions within the EndGame() function
	game->EndGame();

	// Flush all game objects within the buffer. This is important! Otherwise, the game objects will not be deleted, cause memory leaks, and negates the entire purpose of this system.
	gameObjectManager->FlushBuffer();

	// Delete pointers declared within this function
	delete game;
	delete block;
	delete inventoryMan;


	delete player;
	delete gameObjectManager;

	// The software returns a 0 (success) and exits.
	return 0;
}
