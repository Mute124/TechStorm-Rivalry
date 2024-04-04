#pragma once
#include "../Common.h"
#include "../core/ui/UIMenu.h"
#include "../core/utils/Button.h"
#include "../console/Console.h"

namespace TechStormRivalry {
	namespace MainMenu {
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
			const char* m_text = "null";
			Rectangle m_rect;
			Color m_color;

			Vector2 m_textPosition;

			float m_textSize;
			float m_textSpacing;
			int m_alignment = TEXT_ALIGN_LEFT;
			static inline Font m_font;
		public:

			static inline void initTitle() {
				m_font = LoadFont("data/gui/fonts/static/Tektur-ExtraBold.ttf");
			}

			MainMenuTitle(const char* text, Color color, float textSize, float textSpacing) : m_text(text), m_color(color), m_textSize(textSize), m_textSpacing(textSpacing) {
				Vector2 m_textMeasurement = MeasureTextEx(guiFont, m_text, m_textSize, m_textSpacing);

				this->m_textPosition = Vector2{
					GetScreenWidth() / 2.0f,
					GetScreenHeight() / 2.0f - m_textMeasurement.y,
				};

				this->m_rect = Rectangle{
					m_textPosition.x,
					m_textPosition.y,
					100 ,
					m_textMeasurement.y
				};
			}

			void drawElement() override {

				//GuiDrawText(this->m_text, this->m_rect, this->m_alignment, this->m_color);

				DrawTextEx(this->m_font, this->m_text, { this->m_rect.x, this->m_rect.y - 100 }, this->m_textSize, this->m_textSpacing, this->m_color);

				//DrawTextEx(font, m_text, TechStorm::uVec2f((float)m_screenMiddle.x - 100, (float)GetScreenHeight() * 0.05f), 48, 20, WHITE);
			}
		};

		class MenuButton : public TechStorm::UIElement {
		public:
			bool isClicked = false;
			Rectangle rect;
			const char* text;

			bool hide = false;

			MenuButton(Rectangle rect, const char* txt) : rect(rect), text(txt) {
			}

			void drawElement() override {
				isClicked = GuiButton(rect, text);

				// has to be false because it would only play at the end of the collision.
				if (CheckCollisionPointRec(GetMousePosition(), this->rect)) {
					Game::playUIHoverSound();
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
			bool closeMainMenu = false;
			int padding = 150;
			MenuButton* start;
			MenuButton* exitBtn;
			MainMenuTitle* title;
		public:

			MainMenu(Game* game) {
				menuMusic = LoadMusicStream("resources/audio/ost/starstruck.mp3");
				Image backdropImg = game->assets->getImage("background");

				ImageResize(&backdropImg, GetScreenWidth(), GetScreenHeight());
				m_backdrop = LoadTextureFromImage(backdropImg);

				//game->pushRogueElement(consoleUI);

				Rectangle titleBox = Rectangle{
				};
				GuiLoadStyle("data/gui/styles/default.rgs");

				title = new MainMenuTitle(game->wintitle, Color{ 66, 203, 245, 255 }, 45.0f, 10.0f);
				title->initTitle();
				start = new MenuButton(
					Rectangle
					{
						100.0f,
						200.0f,
						250,
						MeasureTextEx(guiFont, "Singleplayer", guiFont.baseSize, guiFont.glyphPadding).y + 80
					},
					"Singleplayer"
				);

				exitBtn = new MenuButton(
					Rectangle
					{
						(float)start->rect.x,
						(float)start->rect.y + padding,
						250,
						MeasureTextEx(guiFont, "Exit To Desktop", guiFont.baseSize, guiFont.glyphPadding).y + 80
					},
					"Exit To Desktop"
				);

				game->pushContainer(this, false, false);
			}

			void drawMenu(Console::ConsoleUI* console) {
				PlayMusicStream(menuMusic);
				bool showExitConfirmation = false;
				Vector2 anchor = { GetScreenWidth() / 2.0f,
							GetScreenHeight() / 2.0f };
				float confirmationBoxPosX = anchor.x - 250;
				float confirmationBoxPosY = anchor.y - 250;

				Rectangle confirmationBox = Rectangle{
							confirmationBoxPosX,
							confirmationBoxPosY,
							500,
							250 };
				float confirmHeight = MeasureTextEx(guiFont, "Confirm", guiFont.baseSize, guiFont.glyphPadding).y + 40;

				Rectangle backBox = Rectangle{
								confirmationBoxPosX + 245 + 8,
								confirmationBoxPosY + (250.0f - (confirmHeight + 10)),
								240.0f,
								confirmHeight
				};

				Rectangle confirmButtonBox = Rectangle{
							confirmationBoxPosX + 8,
							confirmationBoxPosY + (250.0f - (confirmHeight + 10)),
							240.0f,
							confirmHeight
				};

				bool playedHoverSound = false;
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
					start->drawElement();
					exitBtn->drawElement();
					title->drawElement();

					if (start->isClicked) {
						break;
					}

					if (exitBtn->isClicked) {
						showExitConfirmation = true;
						Game::playButtonClick();
					}

					if (exitBtn->isClicked || start->isClicked) {
						Game::playButtonClick();
					}

					if (showExitConfirmation) {
						bool confirmation = GuiWindowBox(confirmationBox, "Are you sure you want to exit?");

						bool confirm = GuiButton(confirmButtonBox, "Confirm");

						bool back = GuiButton(backBox, "Back");

						if (back || confirm || confirmation) {
							Game::playButtonClick();
						}

						if ((back || confirmation)) {
							showExitConfirmation = false;
						}
						else if (confirm) {
							exit(0);
						}
					}

#ifndef TECHSTORM_DEBUG
					DrawCircle(GetMouseX(), GetMouseY(), 2.5f, WHITE);
#endif // TECHSTORM_DEBUG

					Game::drawCursor();
					EndDrawing();
				}

				StopMusicStream(menuMusic);
				Game::appInstance->removeContainer(this->containerID);
				delete this;
			}
		};
	}
}
