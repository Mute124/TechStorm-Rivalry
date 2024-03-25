#pragma once
#include "../core/ui/Menu.h"

class MainMenu : public Menu {
public:
	MainMenu() {
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

		//game->pushRogueElement(consoleUI);
		start->font = game->defaultFont;

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
			game->uiMan->drawUI(EDrawType::DRAW_FINAL);

			EndDrawing();
		}
		StopMusicStream(menuMusic);
	}
};
