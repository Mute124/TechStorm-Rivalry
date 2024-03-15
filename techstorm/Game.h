#pragma once
#include "common.h"
#include "core/rendering/Light.h"
#include "player/Player.h"
#include "core/scripting/ScriptManager.h"
#include "core/rendering/Renderers.h"
#include "core/ui/UIMan.h"
#include <any>

class Game
{
public:
	// Config manager instance
	static inline ConfigMan* configman = new ConfigMan();
	static inline toml::v3::parse_result optionsConfig;
	static inline Renderers* gameRenderers;
	static inline ScriptManager* scriptManager;
	static inline UIMan* uiMan;
	static inline GameobjectManager* objMan;
	static inline Vector2 windowSize = { 0, 0 };
	static inline Vector2 screenMiddle = { 0, 0 };
	Font gameFont;
	int windowWidth;
	int windowHeight;
	int lightCountLoc;
	int emissiveIntensityLoc;
	int emissiveColorLoc;
	int textureTilingLoc;
	float ambientIntensity = 0.02f;
	Color ambientColor = GRAY;
	Vector3 ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
	bool isFullscreen = false;
	bool enableMusic;
	bool loaded;
	Player* player;

	Game() {}

	// deconstructor. This just deletes itself, I guess it is suicide?
	~Game()
	{
		delete this;
	}

	toml::v3::parse_result GetGameConfig()
	{
		return this->optionsConfig;
	}

	Vector2 GetWindowSize() {
		return { (float)windowWidth, (float)windowHeight };
	}

	void init() {
		SetTraceLogCallback(Logman::customLog);

		// Read config to decide what to set for the game
		Logman::customLog(LOG_INFO, "Initiating Config Manager", NULL);

		optionsConfig = toml::parse_file("Config/options.toml");
		Logman::customLog(LOG_INFO, "OptionsConfig file registered", NULL);

		isFullscreen = optionsConfig["Window"]["isFullScreen"].as_boolean();
		Logman::customLog(LOG_INFO, TextFormat("IsFullscreen = %i", isFullscreen), NULL);

		enableMusic = optionsConfig["Sound"]["enableMusic"].as_boolean();
		Logman::customLog(LOG_INFO, TextFormat("EnableMusic = %i", enableMusic), NULL);

		if (isFullscreen == false)
		{
			windowWidth = ConfigTypeConverter::strToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string & ());
			Logman::customLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

			windowHeight = ConfigTypeConverter::strToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string & ());
			Logman::customLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);
		}
		else
		{
			ToggleFullscreen();
			windowWidth = GetMonitorWidth(0);
			windowHeight = GetMonitorHeight(0);

			// windowfactory->StampFlag(FLAG_WINDOW_MAXIMIZED);
		}

		if (windowHeight == 0 || windowWidth == 0)
		{
			Logman::customLog(LOG_ERROR, "WINDOW WIDTH/HEIGHT CANT BE 0! Setting to config data.", NULL);
			if (isFullscreen) {
				windowWidth = GetMonitorWidth(0);
				windowHeight = GetMonitorHeight(0);
			}
			else {
				windowWidth = ConfigTypeConverter::strToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string & ());
				Logman::customLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

				windowHeight = ConfigTypeConverter::strToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string & ());
				Logman::customLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);
			}
		}

		// Stamp window config flags & Manufacture

		Logman::customLog(LOG_INFO, "Starting Game", NULL);

		if (isFullscreen == true) {
			SetConfigFlags(FLAG_WINDOW_MAXIMIZED || FLAG_MSAA_4X_HINT);
		}
		else {
			SetConfigFlags(FLAG_MSAA_4X_HINT);
		}

		InitWindow(windowWidth, windowHeight, "TechStorm-Rivalry");
		InitAudioDevice(); // starts the audio driver(s).

		DisableEventWaiting();

		SetExitKey(KEY_NULL); // In event of your fuck up press this.

		// Setting the window icon in task bar
		Image icon = LoadImage("resources/icons/icon1.png");
		ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		SetWindowIcon(icon);

		Renderers* renderers = new Renderers();

		if (isFullscreen == true) {
			renderers->forwardRenderer->createRenderTexture(GetScreenWidth(), GetScreenHeight());
		}
		else {
			renderers->forwardRenderer->createRenderTexture(windowWidth, windowHeight);
		}

		renderers->forwardRenderer->bloomShader = LoadShader(0, "resources/shaders/bloom.fs");

		objMan = new GameobjectManager();
		uiMan = new UIMan();

		windowSize = { (float)windowWidth, (float)windowHeight };

		screenMiddle = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
		gameFont = LoadFont("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");
		Logman::Log(TextFormat("%f %f: ", screenMiddle.x, screenMiddle.y));
	}

	// called before the game starts, or when the game is reloaded
	void loadGame() {
		// Load the shader into memory
		gameRenderers->forwardRenderer->pbrShader = LoadShader(TextFormat("resources/shaders/glsl%i/pbr.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));

		// Get shader locations
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "albedoMap");

		// WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture They
		// are passed as to the SHADER_LOC_MAP_METALNESS location for convenience, shader already takes
		// care of it accordingly
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "mraMap");
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "normalMap");

		// WARNING: Similar to the MRA map, the emissive map packs different information into a single
		// texture: it stores height and emission data It is binded to SHADER_LOC_MAP_EMISSION location
		// an properly processed on shader
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "emissiveMap");
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "albedoColor");

		// Setup additional required shader locations, including lights data
		gameRenderers->forwardRenderer->pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "viewPos");
		lightCountLoc = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "numOfLights");

		// set it to the value of the MAX_LIGHTS macro and pass it to the shader
		int maxLightCount = MAX_LIGHTS;
		SetShaderValue(game->renderers->forwardRenderer->pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

		// Setup ambient color and intensity (brightness) parameters

		SetShaderValue(game->renderers->forwardRenderer->pbrShader, GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
		SetShaderValue(game->renderers->forwardRenderer->pbrShader, GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

		// Get location for shader parameters that can be modified
		emissiveIntensityLoc = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "emissivePower");
		emissiveColorLoc = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "emissiveColor");
		textureTilingLoc = GetShaderLocation(game->renderers->forwardRenderer->pbrShader, "tiling");

		// Create the player model
		// NOTE: This model is TEMPORARY! It will be deleted after a proper model is made. Refers to the
		// size of the player model. Same process as the default block model creation.
		const int Playersize = 3;
		Model PlayerModel = LoadModelFromMesh(GenMeshCube(Playersize, Playersize, Playersize));

		// Construct the player object
		Player* player = new Player(Vector3{ 0.0f, 2.0f, 4.0f }, 100, PlayerModel, CAMERA_FIRST_PERSON);

		// Finally push it off to the object manager
		game->objMan->pushObject(player);
	}

	void StartGame()
	{
		SetTargetFPS(60);
	}

	void endGame()
	{
		CloseWindow(); // Close window and OpenGL context
		CloseAudioDevice();
		delete configman;
		delete scriptManager;
		delete gameRenderers;
		delete uiMan;
		delete objMan;
		delete this;
	}

	// GRAPHICS
	//_____________________________________________________

	// ForwardRenderer *renderer;
};
