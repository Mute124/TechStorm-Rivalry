#pragma once

#include "core/application/Application.h"

class Game final : public Application
{
public:
	static inline Renderers* gameRenderers;

	int lightCountLoc;
	int emissiveIntensityLoc;
	int emissiveColorLoc;
	int textureTilingLoc;
	float ambientIntensity = 0.02f;
	Color ambientColor = GRAY;
	Vector3 ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
	bool enableMusic;
	bool loaded;
	Player* player;

	Vector2 GetWindowSize() {
		return { (float)winWidth, (float)winHeight };
	}

	void init() {
		try
		{
			this->preInitialize();

			// Stamp window config flags & Manufacture
			// Read config to decide what to set for the game
			this->customLog(LOG_INFO, "Initiating Config Manager", NULL);

			this->customLog(LOG_INFO, "OptionsConfig file registered", NULL);

			//ConfigFile* config = confRegistry->getFile("data\config\options.toml");
			//isFullscreen = config->getBoolEntry("Window", "isFullScreen");
			this->customLog(LOG_INFO, TextFormat("IsFullscreen = %i", isFullscreen), NULL);

			this->customLog(LOG_INFO, TextFormat("EnableMusic = %i", true), NULL);

			// Stamp window config flags & Manufacture

			this->customLog(LOG_INFO, "Starting Game", NULL);
			this->initApplication(800, 600, "Techstorm Rivalry", FLAG_MSAA_4X_HINT);


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
				renderers->forwardRenderer->createRenderTexture(winWidth, winHeight);
			}

			renderers->forwardRenderer->bloomShader = LoadShader(0, "resources/shaders/bloom.fs");

			defaultFont = LoadFont("data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");

			SetTargetFPS(this->targetFPS);
			instance = this;
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
