#pragma once
#include "../core/ui/UIMenu.h"
#include "../core/utils/Button.h"
#include <raylib.h>

namespace TechStormRivalry {
	namespace MainMenu {
		bool closeMainMenu = false;

		class MainMenuBackground : public TechStorm::UIElement {
		private:

		public:
			MainMenuBackground() {
			}

			void drawElement() override {
			}
		};

		class MainMenuTitle : public TechStorm::UIElement {
		private:
			const char* m_text = "TechStorm-Rivalry";
			TechStorm::uVec2i screenMiddle;
		public:

			void initTitle(TechStorm::uVec2i screenMiddle) {
				this->screenMiddle = screenMiddle;
			}

			void drawElement() override {
				DrawTextEx(font, m_text, TechStorm::uVec2f((float)screenMiddle.x - 100, (float)GetScreenHeight() * 0.05f), 48, 20, WHITE);
			}
		};

		class MainMenuStart : public TechStorm::UIElement {
		public:
			TechStorm::ButtonR* button;

			MainMenuStart(TechStorm::ButtonR* button) : button(button) {
				this->button->font = font;
			}

			void drawElement() override {
				if (this != nullptr) {
					button->draw();
				}
				if (button->IsClicked()) {
					this->parent->requestKill();
				}
			}

			void updateElement() override {
			}
		};

		class MainMenu final : public TechStorm::UIMenu {
		private:
			Music menuMusic;
			bool windowUnfocused = false;
			bool windowReFocused = false;
			Texture m_backdrop;

		public:

			MainMenu(Game* game) {
				menuMusic = LoadMusicStream("resources/audio/ost/starstruck.mp3");
				Image backdropImg = LoadImage("resources/textures/background.png");
				ImageResize(&backdropImg, GetScreenWidth(), GetScreenHeight());
				m_backdrop = LoadTextureFromImage(backdropImg);

				//game->pushRogueElement(consoleUI);
				addChild(new MainMenuTitle());
				addChild(new MainMenuStart(new TechStorm::ButtonR("Start", (game->screenMiddle.x - (game->screenMiddle.x) + (sqrt(GetScreenWidth()))), (game->screenMiddle.y - (game->screenMiddle.y) + (sqrt(GetScreenHeight()))))));

				game->pushContainer(this, false, false);
			}

			void drawMenu(Console::ConsoleUI* console) {
				PlayMusicStream(menuMusic);
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

					if (shouldKill) {
						break;
					}
					console->updateElement();

					//this->update();
					UpdateMusicStream(menuMusic);   // Update music buffer with new stream data

					BeginDrawing();
					DrawTextureRec(m_backdrop, Rectangle{ 0, 0, (float)(m_backdrop.width), (float)(-m_backdrop.height) }, Vector2{ 0, 0 }, WHITE);
					console->drawElement();
					this->drawChildren(DRAW_FINAL);

					EndDrawing();
				}

				StopMusicStream(menuMusic);
				Game::appInstance->removeContainer(this->containerID);
				delete this;
			}
		};
	}
}
