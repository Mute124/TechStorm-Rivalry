/*
---------------------------------------------------------------------------------
| 					         Includes											|
---------------------------------------------------------------------------------
*/

#pragma once

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

#include "techstorm/core/threading/ThreadGroups.h"
#include "techstorm/core/ui/UIElement.h"
#include "techstorm/core/ui/UIMan.h"
#include "techstorm/ui/UIFadingMsg.h"
#include "techstorm/core/audio/FxMan.h"
#include "techstorm/globalobj/Objects.h"
#include "techstorm/console/Console.h"
#include "techstorm/core/ui/UIMenu.h"
#include "techstorm/ui/MainMenu.h"
#include "techstorm/ui/PlayerHUD.h"
#include "techstorm/economy/SystemEconomy.h"

#include <time.h>
#include <vector> // needed for game object list

#include <raylib.h>
#include <lua.hpp>
#include <sol/sol.hpp>

// config
#include <toml++/toml.hpp>
#include <tinyxml2.h>

#define NUM_MODELS  9               // Parametric 3d shapes to generate

namespace TechStormRivalry {
	static void mainThread() {

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
		game->init();

		std::thread t([game] {
			game->assets->LoadAssets("resources", "data");
			});

		while (!game->assets->doneLoading) {
			BeginDrawing();
			ClearBackground(BLUE);
			EndDrawing();
		}
		t.join();

		TechStorm::Logman::Log("Main menu ready");
		Console::ConsoleUI* console = new Console::ConsoleUI();
		MainMenu::MainMenu* menu = new MainMenu::MainMenu(game);

		menu->awakeMenu();
		menu->drawMenu(console);

		console = new Console::ConsoleUI();
		game->pushRogueElement(console);

		// Assign already setup PBR shader to model.materials[0], used by models.meshes[0]

		// Create a default block model with a length, width, and height of the value of BLOCK_SIZE.
		// This creates a cube mesh with a length, width, and height of BLOCK_SIZE and then converts it
		// to a model, loading it into memory.
		Model DefaultBlockModel = LoadModelFromMesh(
			GenMeshCube(BLOCK_SIZE, BLOCK_SIZE,
				BLOCK_SIZE)); // this is the default model used in blocksd.

		// todo : change all use instances of DefaultBlockModel to use the global default model.
		SetDefaultModel(DefaultBlockModel);

		// Construct the block object
		Block* block = new Block(Vector3Zero(), WHITE, game->pbrShader, LoadModelFromMesh(GenMeshCylinder(BLOCK_SIZE, BLOCK_SIZE, 100)));

		// Finally push it off to the object manager
		game->pushObject(block);

		// Create the player model
	// NOTE: This model is TEMPORARY! It will be deleted after a proper model is made. Refers to the
	// size of the player model. Same process as the default block model creation.
		const int Playersize = 3;
		Model PlayerModel = LoadModelFromMesh(GenMeshCube(Playersize, Playersize, Playersize));

		// Construct the player object
		Player::Player* player = new Player::Player(Vector3{ 0.0f, 2.0f, 4.0f }, PlayerModel, CAMERA_FIRST_PERSON);

		// Finally push it off to the object manager
		game->pushObject(player);

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

		TechStorm::Light sun = TechStorm::CreateLight(TechStorm::LIGHT_POINT, TechStorm::uVec3f{ 1.0f, 0.0f, 1.0f }, Vector3One(), WHITE, 4.0f, game->pbrShader);

		// The texture for the near death affect initialization
		Texture2D nearDeathTex = { 0 };

		// The image for the near death affect initialization
		Image nearDeathAffect = { 0 };

		// The color for the near death affect initialization
		TechStorm::uColor nearDeathColor = TechStorm::uColor();

		healthBarPositionX = game->winWidth + healthBarOffsetX;
		healthBarPositionY = game->winHeight + healthBarOffsetY;

		DisableCursor();

		PlayerHUD* hud = new PlayerHUD(game);

		Economy::MarketProduct tester = Economy::MarketProduct();
		tester.baseValue = 5;
		tester.supply = 100;

		Economy::Merchant* merchant = new Economy::Merchant();
		merchant->m_market[0] = tester;
		merchant->m_priceUptick = 0.25f;
		Faction::CharacterFaction fa = Faction::CharacterFaction();
		Faction::CharacterFaction fb = Faction::CharacterFaction();

		merchant->m_owner = &fb;
		fa.meetFaction(fb);
		fb.meetFaction(fa);

		while (!WindowShouldClose())
		{
			int scroll = GetMouseWheelMove();

			// Camera PRO usage example (EXPERIMENTAL)
// This new camera function allows custom movement/rotation values to be directly provided
// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
			UpdateCameraPro(player->cameraComponent->getSelfCameraPointer(),
				Vector3{
					(IsKeyDown(player->controller->forward) || IsKeyDown(KEY_UP)) * player->controller->speed -      // Move forward-backward
					(IsKeyDown(player->controller->backward) || IsKeyDown(KEY_DOWN)) * player->controller->speed,
					(IsKeyDown(player->controller->right) || IsKeyDown(KEY_RIGHT)) * player->controller->speed -   // Move right-left
					(IsKeyDown(player->controller->left) || IsKeyDown(KEY_LEFT)) * player->controller->speed,
					(IsKeyDown(player->controller->jump)) * player->controller->speed -                                                 // Move up-down
					(IsKeyDown(player->controller->crouch)) * player->controller->speed
				},
				Vector3{
					GetMouseDelta().x * player->controller->mouseSensitivity,                            // Rotation: yaw
					GetMouseDelta().y * player->controller->mouseSensitivity,                            // Rotation: pitch
					player->controller->CalculateCameraTilt()                // Rotation: roll
				},

				GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)

			// NOTE : This is a very basic implementation of placing an object into the world. This is
			// temporary and should be fleshed out.
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector3 placepos = player->cameraComponent->getTarget();
			}

			if (IsKeyPressed(KEY_ESCAPE))
			{
				// Todo, move the menuCamera to be created on game startup and then hidden. it gets
				// shown on if statement validation
				bool exitMenu = false;
				bool manualExit = false;

				MenuCamera* men_pause = new MenuCamera();
				TechStorm::ButtonR* save = new TechStorm::ButtonR("Save", 100, 100);
				TechStorm::ButtonR* Options = new TechStorm::ButtonR("Options", 100, 200);
				TechStorm::ButtonR* exitButton = new TechStorm::ButtonR("Exit to Windows", 100, 300);

				EnableCursor();
				while (!exitMenu)
				{
					game->updateUI();
					BeginDrawing();

					game->drawUI(DRAW_FINAL);

					save->draw();
					save->updateObjects();

					Options->draw();
					Options->updateObjects();

					exitButton->draw();
					exitButton->updateObjects();

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
					if (IsKeyPressed(KEY_ESCAPE) && exitMenu == false)
					{
						exitMenu = true;
					}
					else if (IsKeyPressed(KEY_ESCAPE) && exitMenu == true)
					{
						break;
					}

					if (manualExit)
					{
						exitMenu = true;
					}
				}

				// cleanup UnloadTexture(tex);
				delete men_pause;
				delete save;
				delete exitButton;
				if (manualExit)
				{
					TechStorm::Logman::customLog(LOG_INFO, "Exiting Game", NULL);
					exit(0);
				}
			}

			if (IsKeyPressed(KEY_E)) {
			}

			if (IsKeyDown(KEY_Y)) {
				player->damage(15);
			}

			if (IsKeyPressed(KEY_B)) {
				merchant->buy(0, 5, fa);
				TechStorm::Logman::Log(TextFormat("Supply %i, Demand %i, buy price %f, sell %f, base %i", merchant->m_market[0].supply, merchant->m_market[0].demand, merchant->m_market[0].buyPrice, merchant->m_market[0].sellPrice, merchant->m_market[0].baseValue));
			}

			if (IsKeyPressed(KEY_K)) {
				Economy::MarketPurchase purchase = merchant->sell(0, 500, fa);

				//player->m_balance += purchase.value;
				TechStorm::Logman::Log(TextFormat("Supply %i, Demand %i, buy price %f, sell %f, base %i", merchant->m_market[0].supply, merchant->m_market[0].demand, merchant->m_market[0].buyPrice, merchant->m_market[0].sellPrice, merchant->m_market[0].baseValue));
			}

			// The player's looking direction is the target of the camera. This is the direction the
			// player is looking TODO : Check relevancy.
			ray.position = player->cameraComponent->getPosition();
			ray.direction = player->cameraComponent->getTarget();

			// Sway timer is equal to swayTimer + frame delta time
			swayTimer += GetFrameTime();

			// sway the camera according to the sway algorithm.
			player->cameraComponent->setTarget(Vector3{ player->cameraComponent->getTarget().x + sin(swayTimer * swaySpeed) * swayAmount, player->cameraComponent->getTarget().y, player->cameraComponent->getTarget().z + cos(swayTimer * swaySpeed) * swayAmount });

			/*
			* 			if (player->health <= 15) {

							// equal to nearDeathTimer + frame delta time
					//nearDeathTimer += GetFrameTime();

							if (nearDeathIntensity >= 255) {
								nearDeathIntensity -= nearDeathIntensity / 2;
							}
							else if ((nearDeathIntensity > 0) && (nearDeathIntensity < 255)) {
								nearDeathIntensity += nearDeathIntensity / 2;
							}
							Image img = LoadImageFromTexture(game->renderer->getRenderTexture().texture);
							nearDeathColor = Color{ 255, 0, 0, (unsigned char)nearDeathIntensity };
							ImageColorTint(&img, nearDeathColor);
							Color* pixels = LoadImageColors(img);
							UpdateTexture(game->renderer->getRenderTexture().texture, pixels);             // Update texture with new image data
							UnloadImageColors(pixels);                  // Unload pixels data from RAM
							UpdateTexture(game->renderer->getRenderTexture().texture, pixels);
						}
			*/

			// Stashes input events for later
			PollInputEvents(); // helps for some reason?

			sun.position = player->cameraComponent->getTarget();

			TechStorm::UpdateLight(game->pbrShader, sun);

			game->updateObjects();

			game->startTexturingStep(player->cameraComponent->getSelfCameraPointer());

			game->updateUI();
			game->drawUI(DRAW_CLIPPABLE);

			//DrawTextureRec(nearDeathTex, Rectangle{ 0, 0, (float)(game->renderer->fboDimensions.x), (float)(-game->renderer->fboDimensions.y) }, TechStorm::uVec2i{ 0, 0 }, WHITE);

			game->startRenderingStep(player->cameraComponent->getSelfCamera());

			SetShaderValue(game->pbrShader, game->textureTilingLoc, &block->blockTextureTiling, SHADER_UNIFORM_VEC2);

			Vector4 carEmissiveColor = ColorNormalize(block->model.materials[0].maps[MATERIAL_MAP_EMISSION].color);
			SetShaderValue(game->pbrShader, game->emissiveColorLoc, &carEmissiveColor, SHADER_UNIFORM_VEC4);

			// How bright should the object emit it's emission color.
			float emissiveIntensity = 0.1f;
			SetShaderValue(game->pbrShader, game->emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);

			game->renderObjects();

			game->endRenderingStep();
			game->endTexturingStep();

			game->startDrawingstep();
			game->drawUI(DRAW_FINAL);

			game->endDrawingStep();
		}

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

		game->endGame();

		delete game;
		delete block;

		//delete man;
		delete player;
	}
}
int main()
{
	try
	{
		// Run the game
		std::thread t(std::move(TechStormRivalry::mainThread));

		//scriptManager->startScriptMan(true);
		t.join();
	}
	catch (const std::exception& e)
	{
		TechStorm::Logman::Log(e.what());
	}

	return 0;
}