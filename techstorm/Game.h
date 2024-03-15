#pragma once
#include "common.h"
#include "core/rendering/Light.h"
#include "player/Player.h"
#include "core/scripting/ScriptManager.h"
#include "core/rendering/Renderers.h"
#include "core/ui/UIMan.h"
#include "lua/LuaManager.h"
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
	static inline LuaManager* lua;
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
	}

	void StartGame()
	{
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
		lua = new LuaManager();
		windowSize = { (float)windowWidth, (float)windowHeight };

		screenMiddle = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
		gameFont = LoadFont("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");
		Logman::Log(TextFormat("%f %f: ", screenMiddle.x, screenMiddle.y));

		lua->init();

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
private:
};
