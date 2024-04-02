#pragma once

#include "core/application/Application.h"
#include "core/rendering/Renderer.h"

//#include "techstorm/core/enum/EGameState.h"
namespace TechStormRivalry {
	class Game final : public TechStorm::Application
	{
	public:

		//EGameState currentScreen = Main;
		bool enableMusic;
		bool loaded;

		Game() {}

		Vector2 GetWindowSize() {
			return { (float)winWidth, (float)winHeight };
		}

		TechStorm::Application* getApplication() {
			return appInstance;
		}

		void init() {
			try
			{
				this->preInitialize();

				// Stamp window config flags & Manufacture
				// Read config to decide what to set for the game
				this->customLog(LOG_INFO, "Initiating Config Manager", NULL);

				ConfigFile* config = confRegistry->getFile("options.toml");
				isFullscreen = config->file.entry.Data["Window"]["isFullScreen"].as_boolean()->operator const bool& ();

				int wWidth = config->file.entry.Data["Window"]["windowWidth"].as_integer()->operator const int64_t & ();
				int wHeight = config->file.entry.Data["Window"]["windowHeight"].as_integer()->operator const int64_t & ();
				const char* wTitle = config->file.entry.Data["Game"]["title"].as_string()->operator const std::string & ().c_str();

				if (isFullscreen == true) {
					this->initDisplay(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), wTitle, FLAG_MSAA_4X_HINT);
					this->initApplication(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), wTitle, FLAG_MSAA_4X_HINT);

					//rlglInit(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
				}
				else {
					this->initDisplay(wWidth, wHeight, wTitle, FLAG_MSAA_4X_HINT);
					this->initApplication(wWidth, wHeight, wTitle, FLAG_MSAA_4X_HINT);

					//rlglInit(wWidth, wHeight);
				}

				DisableEventWaiting();

				SetExitKey(KEY_NULL); // In event of your fuck up press this.

				// Setting the window icon in task bar
				Image icon = LoadImage("resources/icons/icon1.png");
				ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
				SetWindowIcon(icon);

				defaultFont = LoadFont("data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");

				SetTargetFPS(this->targetFPS);
				DisableEventWaiting();
				instance = this;

				if (!DirectoryExists("temp"))
				{
					system("mkdir temp"); // run the system command to create the folder. Note : This is a windows command.
				}
			}
			catch (const std::exception& e)
			{
				this->Error(e.what());
			}
		}

		void endGame() {
			CloseWindow(); // Close window and OpenGL context
			CloseAudioDevice();
		}

	private:
	};
}
