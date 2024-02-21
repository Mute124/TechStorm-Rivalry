#pragma once
#include "common.h"
#include "core/rendering/Light.h"
#include "core/player/Player.h"
#include "core/scripting/ScriptManager.h"

class Game
{
	toml::v3::parse_result optionsConfig;
public:
	
	// handles rendering
	class Renderer
	{
	public:
		// start drawing mode
		void startDraw()
		{
			isDrawing = true;
			BeginDrawing();
		}

		// end draing move
		void endDraw()
		{
			isDrawing = false;
			EndDrawing();
		}

		// start 3d drawing
		void Start3D(Camera* camera)
		{
			if (!isDrawing)
			{
				startDraw();
			}
			else
			{
				isIn3DMode = true;
				BeginMode3D(*camera);
			}
		}

		// end 3d drawing
		void end3D()
		{
			if (isIn3DMode && isDrawing)
			{
				EndMode3D();
				isIn3DMode = false;
			}
		}

		// start baking to fbo
		void startTexturing()
		{
			// StartDraw();
			BeginTextureMode(fbo);
			ClearBackground(BLACK);
		}

		// start shadow mapping
		void StartDepthMode()
		{
			BeginTextureMode(depthMapFBO);
		}

		// stop shadow mapping
		void StopDepthMode()
		{
			EndTextureMode();
		}

		// stop baking to fbo
		void stopTexturing()
		{
			// EndDraw();
			EndTextureMode();
		}

		// Create the FBO and depth map FBO
		void CreateRenderTexture(int width, int height)
		{
			fbo = LoadRenderTexture(width, height);
			depthMapFBO = LoadRenderTexture(width, height);
		}

		RenderTexture2D fbo; // FBO render texture
		RenderTexture2D depthMapFBO; // shadowmap.

		// pbr shader
		Shader pbrShader;
		// bloom shader
		Shader bloomShader;

	private:
		bool isDrawing;
		bool isIn3DMode;
	};

	int windowWidth;
	int windowHeight;

	bool isFullscreen = false;
	bool enableMusic;

	// Config manager instance
	ConfigMan* configman = new ConfigMan();

	// renderer instance
	static inline Renderer* renderer;
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


		renderer = new Renderer();


		if (isFullscreen == true) {
			renderer->CreateRenderTexture(GetScreenWidth(), GetScreenHeight());

		}
		else {
			renderer->CreateRenderTexture(windowWidth, windowHeight);

		}

		renderer->bloomShader = LoadShader(0, "resources/shaders/bloom.fs");

		scriptManager = new ScriptManager();

		scriptManager->start();

		// simply a optimization
		rlSetCullFace(RL_CULL_FACE_BACK);

		SetTargetFPS(60);
	}

	void endGame()
	{
		rlglClose();
		CloseWindow(); // Close window and OpenGL context
		CloseAudioDevice();
		delete configman;
		delete scriptManager;
		delete renderer;
		delete this;
	}

	// GRAPHICS
	//_____________________________________________________

	// Renderer *renderer;
};