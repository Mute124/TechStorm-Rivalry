/*
---------------------------------------------------------------------------------
| 					         Includes											|
---------------------------------------------------------------------------------
*/

#include "Math.h"
#include "techstorm/common.h"
#include "techstorm/core/utils/Button.h" // TODO : Can this be moved to common.h?

// Game Engine Includes
#include "techstorm/Game.h"
#include "techstorm/globalobj/Block.h"
#include "techstorm/core/obj/Gameobject.h"
#include "techstorm/core/gamescreen/MenuCamera.h"
#include "techstorm/player/Player.h"
#include "techstorm/core/rendering/Light.h"
#include "techstorm/core/enum/EGameState.h"
#include "techstorm/core/threading/ThreadGroups.h"
#include "techstorm/core/ui/UIElement.h"
#include "techstorm/core/ui/UIMan.h"
#include "techstorm/ui/UIFadingMsg.h"
#include "techstorm/core/audio/FxMan.h"
#include "techstorm/globalobj/Objects.h"
#include "techstorm/core/physics/GravityWells.h"
#include "techstorm/core/physics/PhysObject.h"
#include "techstorm/console/Console.h"
#include "techstorm/core/physics/PhysMan.h"
#include "techstorm/core/physics/ChronoTest.h"
// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126

// std library includes. TODO : Is this still needed?
#include <time.h>
#include <vector> // needed for game object list

#define NUM_MODELS  9               // Parametric 3d shapes to generate

void mainThread() {
	//TODO: Is this still relevant?
	EGameState currentScreen = Main;
	// Booleans

// Lets the program know if the game should use HDR as the skybox
	bool useHDR = true;

	// Initialie the condition for the breathing sound.
	bool isBreathing = false;

	// Viewsway
	float swayAmount = 0.0003f; // how much should the view sway be affected.
	float swaySpeed = 0.02f; // how fast should camera sway
	float swayTimer = 0.0f; // Dont mess with this. it will fuck up the swaying.

	/*
	* Near death affect.
	* Important :
	*	THESE ARE REQUIRED FOR THE ARCH ALGORITHM TO WORK!
	*	See Math.h for the Arch algorithm explanation and uses.
	*
	* Note:
	*	Use a graphing calculator to visualize the algorithm
	*/
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

	// Create game & load it into memory.
	Game* game = new Game();

	// Start the game and do any needed setup
	game->StartGame();

	// IMPORTANT : Do not remove this or delete it as it is the manager of all game objects! (it will fuck up everything)

	// test if temp folder exists, if not create it
	// currently not used for anything
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

	/*
	---------------------------------------------------------------------------------
	| 					        Shader Setup										|
	---------------------------------------------------------------------------------
	*/

	// declare main menu variables here :
	bool closeMainMenu = false;
	bool windowUnfocused = false;
	bool windowReFocused = false;
	//RenderTexture mainMenuTexture = LoadRenderTexture(game->windowWidth, game->windowHeight);
	Image backdropImg = LoadImage("resources/textures/background.png");
	ImageResize(&backdropImg, GetScreenWidth(), GetScreenHeight());
	Texture backdrop = LoadTextureFromImage(backdropImg);
	Music menuMusic = LoadMusicStream("resources/audio/ost/starstruck.mp3");
	ButtonR* start = new ButtonR("Start", game->screenMiddle.x - (game->screenMiddle.x) + 100, game->screenMiddle.y);

	Console::ConsoleUI* consoleUI = new Console::ConsoleUI();

	game->uiMan->pushRogueElement(consoleUI);
	start->font = game->gameFont;

	PlayMusicStream(menuMusic);

	Logman::Log("Main menu ready");

	while (!closeMainMenu) {
		// check eligibility.
		if (WindowShouldClose()) {
			closeMainMenu = true;
		}

		// pause and unpause music depending on focus
		if (!IsWindowFocused()) {
			PauseMusicStream(menuMusic);
			windowReFocused = false;
			windowUnfocused = true;
		}
		else if ((IsWindowFocused() == true) && (windowUnfocused == true)) {
			windowUnfocused = false;
			windowReFocused = true;
			ResumeMusicStream(menuMusic);
		}

		if (start->IsClicked()) {
			break;
		}

		UpdateMusicStream(menuMusic);   // Update music buffer with new stream data
		game->uiMan->update();
		BeginDrawing();

		// ALWAYS ON TOP!
		DrawTextureRec(backdrop, Rectangle{ 0, 0, (float)(backdrop.width), (float)(backdrop.height) }, Vector2{ 0, 0 }, WHITE);
		start->draw();
		DrawTextEx(game->gameFont, "TechStorm-Rivalry", Vector2{ game->screenMiddle.x - 100, (float)GetScreenHeight() * 0.05f }, 48, 20, WHITE);
		game->uiMan->draw(EDrawType::DRAW_FINAL);

		EndDrawing();
	}
	StopMusicStream(menuMusic);

	delete start;

	// Load the shader into memory
	game->gameRenderers->forwardRenderer->pbrShader = LoadShader(TextFormat("resources/shaders/glsl330/pbr.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl330/pbr.fs", GLSL_VERSION));

	// Get shader locations
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "albedoMap");

	// WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture They
	// are passed as to the SHADER_LOC_MAP_METALNESS location for convenience, shader already takes
	// care of it accordingly
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "mraMap");
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "normalMap");

	// WARNING: Similar to the MRA map, the emissive map packs different information into a single
	// texture: it stores height and emission data It is binded to SHADER_LOC_MAP_EMISSION location
	// an properly processed on shader
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "emissiveMap");
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "albedoColor");

	// Setup additional required shader locations, including lights data
	game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "viewPos");
	int lightCountLoc = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "numOfLights");

	// set it to the value of the MAX_LIGHTS macro and pass it to the shader
	int maxLightCount = MAX_LIGHTS;
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

	// Setup ambient color and intensity (brightness) parameters
	float ambientIntensity = 0.02f;
	Color ambientColor = GRAY;
	Vector3 ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

	// Get location for shader parameters that can be modified
	int emissiveIntensityLoc = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "emissivePower");
	int emissiveColorLoc = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "emissiveColor");
	int textureTilingLoc = GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "tiling");

	// Assignment of shaders
	// NOTE: By default, the texture maps are always used
	int usage = 1;
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);

	// Create a default block model with a length, width, and height of the value of BLOCK_SIZE.
	// This creates a cube mesh with a length, width, and height of BLOCK_SIZE and then converts it
	// to a model, loading it into memory.
	Model DefaultBlockModel = LoadModelFromMesh(
		GenMeshCube(BLOCK_SIZE, BLOCK_SIZE,
			BLOCK_SIZE)); // this is the default model used in blocksd.

	// todo : change all use instances of DefaultBlockModel to use the global default model.
	SetDefaultModel(DefaultBlockModel);

	// Construct the block object
	Block* block = new Block(Vector3Zero(), WHITE, game->gameRenderers->forwardRenderer->pbrShader, DefaultBlockModel);

	// Finally push it off to the object manager
	game->objMan->pushObject(block);

	// Create the player model
// NOTE: This model is TEMPORARY! It will be deleted after a proper model is made. Refers to the
// size of the player model. Same process as the default block model creation.
	const int Playersize = 3;
	Model PlayerModel = LoadModelFromMesh(GenMeshCube(Playersize, Playersize, Playersize));

	// Construct the player object
	Player* player = new Player(Vector3{ 0.0f, 2.0f, 4.0f }, 100, PlayerModel, CAMERA_FIRST_PERSON);

	// Finally push it off to the object manager
	game->objMan->pushObject(player);

	// Skybox geometry generation step
	Mesh skyboxMesh = GenMeshCube(1.0f, 1.0f, 1.0f);

	// Skybox model loading step
	Model skybox = LoadModelFromMesh(skyboxMesh);

	// Load skybox shader and set required locations step
	// NOTE: Some locations are automatically set at shader loading
	skybox.materials[0].shader = LoadShader("resources/skybox.vs", "resources/skybox.fs");

	// since the compiler complains about the references of such, these three vars are for the
	// skybox shaders. They will be deleted after.
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

	// Load cubemap shader and setup required shader locations
	Shader shdrCubemap =
		LoadShader("resources/cubemap.vs", "resources/cubemap.fs");

	// set shdrCubemap's equirectangular map.
	const static int equimap = 0;
	SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), &equimap, SHADER_UNIFORM_INT);

	// Note: The filename is hardcoded here and also has a limit of 256 characters! I will be
	// dissapointed if you somehow dont know what that variable does...
	char skyboxFileName[256] = { 0 };

	// This is the panoramic texture, It is used IF useHDR is true
	Texture2D panorama = { 0 };

	if (useHDR)
	{
		TextCopy(skyboxFileName, "resources/milkyWay.hdr");

		// Load HDR panorama (sphere) texture
		panorama = LoadTexture(skyboxFileName);

		// Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR texture NOTE 1:
		// New texture is generated rendering to texture, shader calculates the sphere->cube
		// coordinates mapping NOTE 2: It seems on some Android devices WebGL, fbo does not properly
		// support a FLOAT-based attachment, despite texture can be successfully created.. so using
		// PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
		//skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(
		//	shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
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

	// ----------------------------------------------------------------------------- Light Setup -----------------------------------------------------------------------------

	// Create the Sunlight Note : this is not it's final form, it is just a placeholder for testing
	// ToDo: finalize this step and functionality
	Light sun = CreateLight(LIGHT_POINT, Vector3{ 1.0f, 0.0f, 1.0f }, Vector3One(),
		WHITE, 4.0f, game->gameRenderers->forwardRenderer->pbrShader); // Ambient color.;

	// Enable the sun as a precautionary measure.
	sun.enabled = true;

	// TODO : Is this still relevant and figure out what the hell this does.
	Vector3 Orgin = Vector3
	{
		player->cameraComponent->getPosition().x,
		player->cameraComponent->getPosition().y - 10.0f,
		player->cameraComponent->getPosition().z
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

	// the below lines are just me messing with heightmaps.
	Image cell = GenImageCellular(100, 100, 2);
	Image perlin = GenImagePerlinNoise(100, 100, 1, 0.5f, 1.0f);
	//ImageDraw(&perlin, cell, Rectangle{0, 0, (float)cell.width, (float)cell.height}, Rectangle{0, 0, (float)perlin.width, (float)perlin.height}, WHITE);

	ImageAlphaMask(&perlin, cell);
	Mesh test = GenMeshHeightmap(perlin, Vector3{ 100, 100, 100 });

	// end of height map tomfoolery

	// set default line spacing to 48.
	SetTextLineSpacing(48);
	//TestInteractive::init();
	//TestInteractive::setShader(game->renderers->forwardRenderer->pbrShader);
	GravityWells* wells = new GravityWells();

	wells->ndTester();

	game->objMan->pushObject(wells->gravWells[0]);

	PhysObject* obj = new PhysObject();
	obj->init(game->gameRenderers->forwardRenderer->pbrShader);

	game->objMan->pushObject(obj);

	DisableCursor();

	for (int i = 0; i < 100; i++) {
		game->objMan->pushObject(new PhysObject(game->gameRenderers->forwardRenderer->pbrShader, Vector3Random(1, 6)));
	}
	Crosshair* crosshair = new Crosshair(game->screenMiddle, game->uiMan);
	float brightness = 10.0f;

	SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "brightness"), &brightness, UNIFORM_FLOAT);

	// Now we can run the game loop and start playing!
	while (!WindowShouldClose())
	{
		int scroll = GetMouseWheelMove();
		UpdateCamera(player->cameraComponent->getSelfCameraPointer(), CAMERA_FIRST_PERSON); // Update camera

		// NOTE : This is a very basic implementation of placing an object into the world. This is
		// temporary and should be fleshed out.
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			Vector3 placepos = player->cameraComponent->getTarget();
			//new Block(Vector3{ roundf(placepos.x), roundf(placepos.y), roundf(placepos.z) }, WHITE, game->renderers->forwardRenderer->pbrShader, GetDefaultModel());
			//tester = new TestInteractive(Vector3{ roundf(placepos.x), roundf(placepos.y), roundf(placepos.z) }, WHITE, game->renderers->forwardRenderer->pbrShader, GetDefaultModel());

			///tester->create(Vector3{ roundf(placepos.x), roundf(placepos.y), roundf(placepos.z) }, GetDefaultModel(), 1.0f, WHITE, block->model.materials[0]);
			//gameObjectManager->pushObject(tester);

			PhysObject* ob = new PhysObject();
			ob->init(game->gameRenderers->forwardRenderer->pbrShader, placepos);

			//ob->vel.vel = Vector3AddValue(GetCameraForward(player->cameraComponent->getSelfCameraPointer()), 1.0f);

			game->objMan->pushObject(ob);
		}
		//TestInteractive::setCam(player->cameraComponent->getSelfCamera());
		// Take a screenshot
		if (IsKeyPressed(KEY_F9))
		{
			// take a screenshot
			for (int i = 0; i < INT_MAX; i++)
			{
				const char* fileName = TextFormat("screenshots/screen%i.png", i);
				// if there isnt a duplicate file, it then will create a screenshot.
				if (FileExists(fileName) == 0)
				{
					std::ofstream outfile(fileName);

					outfile.close();
					ExportImage(LoadImageFromTexture(game->gameRenderers->forwardRenderer->fbo.texture), fileName);

					break;
				}
			}
		}

		// Sprinting Mechanic
		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			player->controller->isRunning = true;
		}
		else
		{
			player->controller->isRunning = false;
		}

		// NOTE : This is temporary and is only to test the health system
		if (IsKeyDown(KEY_Y))
		{
			//player->healthComp->damagePlayer(5.0f);
		}

		/*
		---------------------------------------------------------------------------------
		| 					         If Statements go here!								|
		---------------------------------------------------------------------------------
		*/
		// TODO : Move input crap into another thread. Pause Menu
		if (IsKeyPressed(KEY_ESCAPE))
		{
			// Todo, move the menuCamera to be created on game startup and then hidden. it gets
			// shown on if statement validation
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

				save->draw();
				save->updateObjects();

				Options->draw();
				Options->updateObjects();

				exitButton->draw();
				exitButton->updateObjects();

				if (save->IsClicked())
				{
					// todo : implement Saving game data, probably use the Objects vector.
					const char* filename = "save.sav";

					std::vector<void*> data;

					for (int i = 0; i < game->objMan->threadSafeObjects.size(); i++)
					{
						data.push_back(game->objMan->threadSafeObjects[i]);
					}
					SaveFileData(filename, &data, sizeof(data));

					Logman::customLog(LOG_DEBUG, LoadFileText(filename), NULL);
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
			// cleanup UnloadTexture(tex);
			delete men_pause;
			delete save;
			delete exitButton;
			if (manualExit)
			{
				Logman::customLog(LOG_INFO, "Exiting Game", NULL);
				break;
			}
		}

		if (IsKeyPressed(KEY_E)) {
		}

		// The player's looking direction is the target of the camera. This is the direction the
		// player is looking TODO : Check relevancy.
		ray.position = player->cameraComponent->getPosition();
		ray.direction = player->cameraComponent->getTarget();

		// Sway timer is equal to swayTimer + frame delta time
		swayTimer += GetFrameTime();

		// sway the camera according to the sway algorithm.
		//player->cameraComponent->setTarget(Vector3{ player->cameraComponent->getTarget().x + sin(swayTimer * swaySpeed) * swayAmount, player->cameraComponent->getTarget().y, player->cameraComponent->getTarget().z + cos(swayTimer * swaySpeed) * swayAmount });

		if (player->health <= 15) {
			// equal to nearDeathTimer + frame delta time
			nearDeathTimer += GetFrameTime();

			// Arch algorithm implementation for color
			nearDeathIntensity = ArchAlgorithm(amplitude, frequency, nearDeathTimer, steepness, offset, 255, scaleFactor);

			// what color the screen should pulsate
			nearDeathColor = Color{ (unsigned char)nearDeathIntensity, 0, 0, 100 };

			// convert nearDeathColor to an image
			nearDeathAffect = GenImageColor(game->gameRenderers->forwardRenderer->fbo.texture.width, game->gameRenderers->forwardRenderer->fbo.texture.height, nearDeathColor);

			// Set the ambient color to the normalized nearDeathColor
			Vector3 nearDeathAmb = Vector3{ nearDeathColor.r / 255.0f, nearDeathColor.g / 255.0f, nearDeathColor.b / 255.0f };
			// Inform the shader about the new ambient color.
			SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, GetShaderLocation(game->gameRenderers->forwardRenderer->pbrShader, "ambientColor"), &nearDeathAmb, SHADER_UNIFORM_VEC3);

			// Load the image into the texture
			nearDeathTex = LoadTextureFromImage(nearDeathAffect);
			UnloadImage(nearDeathAffect); // We can unload the image now that we have the texture.
		}

		// Stashes input events for later
		PollInputEvents(); // helps for some reason?

		// Where the player's camera is. We need to have this as a float array for the shader
		float cameraPos[3] =
		{
			player->cameraComponent->getPosition().x,
			player->cameraComponent->getPosition().y,
			player->cameraComponent->getPosition().z
		};

		// Update light position
		sun.position = player->cameraComponent->getPosition();

		// Update the shader with the new light data. Note : any shader that uses lighting will need
		// this data!
		UpdateLight(game->gameRenderers->forwardRenderer->pbrShader, sun);
		UpdateLight(game->gameRenderers->forwardRenderer->bloomShader, sun);

		// Send the camera position to the shader
		SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, game->gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW], &cameraPos, SHADER_UNIFORM_VEC3);

		// Update the game object manager
		game->objMan->updateObjects();

		// Start texturing the FBO with what the user will be seeing. This includes UI and Scene objects.
		game->gameRenderers->forwardRenderer->startTexturing();

		game->uiMan->update();
		game->uiMan->draw(DRAW_CLIPPABLE);

		DrawTextureRec(nearDeathTex, Rectangle{ 0, 0, (float)(game->gameRenderers->forwardRenderer->fbo.texture.width), (float)(-game->gameRenderers->forwardRenderer->fbo.texture.height) }, Vector2{ 0, 0 }, WHITE);

		//BeginShaderMode(game->gameRenderers->forwardRenderer->bloomShader);
		BeginMode3D(player->cameraComponent->getSelfCamera());

		// Set old car model texture tiling, emissive color and emissive intensity parameters on shader
		SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, textureTilingLoc, &block->blockTextureTiling, SHADER_UNIFORM_VEC2);

		// Normalize the Emissive map into a 0-1 range. Note : This turns the map into a Vector4,
		// not a color.
		Vector4 carEmissiveColor = ColorNormalize(block->model.materials[0].maps[MATERIAL_MAP_EMISSION].color);
		SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, emissiveColorLoc, &carEmissiveColor, SHADER_UNIFORM_VEC4);

		// How bright should the object emit it's emission color.
		float emissiveIntensity = 0.01f;
		SetShaderValue(game->gameRenderers->forwardRenderer->pbrShader, emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);

		// Render all game objects
		//rlEnableWireMode();
		game->objMan->renderObjects();
		// end 3d rendering and texturing.
		game->gameRenderers->forwardRenderer->end3D();

		//EndShaderMode();
		game->gameRenderers->forwardRenderer->stopTexturing();

		/*
		---------------------------------------------------------------------------------
		|     2d Ui rendering for AFTER 3d drawing										|
		---------------------------------------------------------------------------------
		*/
		//UIMan::draw();

		// Warning : DO NOT MOVE THIS! this is important! due to a bug within raylib, this must be
		// done after the texturing is done or a stack overflow WILL occur. GOD DAMN IT!
		rlPopMatrix();

		/*
		---------------------------------------------------------------------------------
		| 					Post Process Affects										|
		---------------------------------------------------------------------------------
		*/
		SetTextureFilter(game->gameRenderers->forwardRenderer->fbo.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
		game->gameRenderers->forwardRenderer->startDraw();
		// Begin drawing mode so we can actually see stuff!

		// We must tell OpenGL that we want to use the bloom shader on the FBO!
		//BeginShaderMode(game->renderers->forwardRenderer->bloomShader);

		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
		DrawTextureRec(game->gameRenderers->forwardRenderer->fbo.texture, Rectangle{ 0, 0, (float)(game->gameRenderers->forwardRenderer->fbo.texture.width), (float)(-game->gameRenderers->forwardRenderer->fbo.texture.height) }, Vector2{ 0, 0 }, WHITE);

		// tell OpenGL that we no longer need the bloom shader to be active. so in other words tell it to fuck off.
		//EndShaderMode();

		// Draw the FPS onto the screen.
		DrawFPS(100, 100);

		game->uiMan->draw(DRAW_FINAL);

		// Let raylib know that we're done drawing to the screen.
		game->gameRenderers->forwardRenderer->endDraw();

		// clear the screen and replace it with black.
		ClearBackground(BLACK);
	}

	/*
	---------------------------------------------------------------------------------
	| 					           Unloading										|
	---------------------------------------------------------------------------------
	*/

	// Unload models. Note : Technically we dont need to unload models as they get automatically
	// unloaded, but it is still good practice. Same goes with textures.
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
	game->endGame();

	// Flush all game objects within the buffer. This is important! Otherwise, the game objects will
	// not be deleted, cause memory leaks, and negates the entire purpose of this system.
	game->objMan->flushBuffer();
	//threadGroups.join();

	// Delete pointers declared within this function
	delete game;
	delete block;

	delete player;

	// The software returns a 0 (success) and exits.
}

void otherTest() {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1000;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - mesh generation");

	// We generate a checked image for texturing
	Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
	Texture2D texture = LoadTextureFromImage(checked);
	UnloadImage(checked);

	Model models[NUM_MODELS] = { 0 };

	models[0] = LoadModelFromMesh(GenMeshPlane(2, 2, 4, 3));
	models[1] = LoadModelFromMesh(GenMeshCube(2.0f, 1.0f, 2.0f));
	models[2] = LoadModelFromMesh(GenMeshSphere(2, 32, 32));
	models[3] = LoadModelFromMesh(GenMeshHemiSphere(2, 16, 16));
	models[4] = LoadModelFromMesh(GenMeshCylinder(1, 2, 16));
	models[5] = LoadModelFromMesh(GenMeshTorus(0.25f, 4.0f, 16, 32));
	models[6] = LoadModelFromMesh(GenMeshKnot(1.0f, 2.0f, 16, 128));
	models[7] = LoadModelFromMesh(GenMeshPoly(5, 2.0f));
	models[8] = LoadModelFromMesh(GenMeshHeightmap(GenImageCellular(100, 100, 2), Vector3AddValue(Vector3Zero(), 5)));

	// Generated meshes could be exported as .obj files
	//ExportMesh(models[0].meshes[0], "plane.obj");
	//ExportMesh(models[1].meshes[0], "cube.obj");
	//ExportMesh(models[2].meshes[0], "sphere.obj");
	//ExportMesh(models[3].meshes[0], "hemisphere.obj");
	//ExportMesh(models[4].meshes[0], "cylinder.obj");
	//ExportMesh(models[5].meshes[0], "torus.obj");
	//ExportMesh(models[6].meshes[0], "knot.obj");
	//ExportMesh(models[7].meshes[0], "poly.obj");
	//ExportMesh(models[8].meshes[0], "custom.obj");

	// Set checked texture as default diffuse component for all models material
	for (int i = 0; i < NUM_MODELS; i++) models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	// Define the camera to look into our 3d world
	Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

	// Model drawing position
	Vector3 position = { 0.0f, 0.0f, 0.0f };

	int currentModel = 0;
	bool isDirty = false;
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentModel = (currentModel + 1) % NUM_MODELS; // Cycle between the textures
		}

		if (IsKeyDown(KEY_C)) {
			camera.position.y -= 0.5f;
		}

		if (IsKeyDown(KEY_SPACE)) {
			camera.position.y += 0.5f;
		}

		if (IsKeyPressed(KEY_P)) rlEnablePointMode();

		if (IsKeyPressed(KEY_RIGHT))
		{
			currentModel++;
			if (currentModel >= NUM_MODELS) currentModel = 0;

			if (currentModel == 8) {
				isDirty = true;
			}
		}
		else if (IsKeyPressed(KEY_LEFT))
		{
			currentModel--;
			if (currentModel < 0) currentModel = NUM_MODELS - 1;
		}
		//----------------------------------------------------------------------------------

		if (IsKeyPressed(KEY_Y)) {
			models[8] = LoadModelFromMesh(GenMeshHeightmap(GenImageCellular(100, 100, 2), Vector3AddValue(Vector3Zero(), 5)));
			models[8].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
		}
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);

		DrawModel(models[currentModel], position, 1.0f, WHITE);
		DrawGrid(10, 1.0);

		EndMode3D();

		DrawRectangle(30, 400, 310, 30, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(30, 400, 310, 30, Fade(DARKBLUE, 0.5f));
		DrawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL MODELS", 40, 410, 10, BLUE);

		switch (currentModel)
		{
		case 0: DrawText("PLANE", 680, 10, 20, DARKBLUE); break;
		case 1: DrawText("CUBE", 680, 10, 20, DARKBLUE); break;
		case 2: DrawText("SPHERE", 680, 10, 20, DARKBLUE); break;
		case 3: DrawText("HEMISPHERE", 640, 10, 20, DARKBLUE); break;
		case 4: DrawText("CYLINDER", 680, 10, 20, DARKBLUE); break;
		case 5: DrawText("TORUS", 680, 10, 20, DARKBLUE); break;
		case 6: DrawText("KNOT", 680, 10, 20, DARKBLUE); break;
		case 7: DrawText("POLY", 680, 10, 20, DARKBLUE); break;
		case 8: DrawText("Custom (triangle)", 580, 10, 20, DARKBLUE); break;
		default: break;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(texture); // Unload texture

	// Unload models data (GPU VRAM)
	for (int i = 0; i < NUM_MODELS; i++) UnloadModel(models[i]);

	CloseWindow();          // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}

int main()
{
	try
	{
		please();
		// Run the game
		std::thread t(std::move(mainThread));

		ScriptManager* scriptManager = new ScriptManager();

		scriptManager->start(true);
		t.join();
	}
	catch (const std::exception& e)
	{
		Logman::Log(e.what());
	}

	return 0;
}
