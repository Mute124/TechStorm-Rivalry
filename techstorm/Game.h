#pragma once
#include "common.h"
#include "core/rendering/Light.h"
#include "core/player/Player.h"
#include "core/scripting/ScriptManager.h"
#include "core/rendering/Renderers.h"

class Game final
{
private:
	toml::v3::parse_result optionsConfig;
public:

	static inline Game* instance = nullptr;

	static inline Vector2 windowSize = { 0, 0 };

	int windowWidth;
	int windowHeight;

	bool isFullscreen = false;
	bool enableMusic;

	// Config manager instance
	ConfigMan* configman = new ConfigMan();

	Layers* layers;
	Renderers* renderers;

	static inline ScriptManager* scriptManager;

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

		SetExitKey(KEY_BACKSPACE); // In event of your fuck up press this.

		// Setting the window icon in task bar
		Image icon = LoadImage("resources/images/icon.png");
		ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		SetWindowIcon(icon);


		layers->init();

		Renderers* renderers = new Renderers();


		if (isFullscreen == true) {
			renderers->forwardRenderer->createRenderTexture(GetScreenWidth(), GetScreenHeight());

		}
		else {
			renderers->forwardRenderer->createRenderTexture(windowWidth, windowHeight);

		}

		renderers->forwardRenderer->bloomShader = LoadShader(0, "resources/shaders/bloom.fs");

		scriptManager = new ScriptManager();

		scriptManager->start();

		// simply a optimization
		rlSetCullFace(RL_CULL_FACE_BACK);

		SetTargetFPS(60);

		instance = this;

		windowSize = { (float)windowWidth, (float)windowHeight };
	}

	void endGame()
	{
		rlglClose();
		CloseWindow(); // Close window and OpenGL context
		CloseAudioDevice();
		delete configman;
		delete scriptManager;
		delete renderers;
		delete this;
	}

	// GRAPHICS
	//_____________________________________________________

	// ForwardRenderer *renderer;
};